#include "CreditManager.h"
#include <iomanip>
#include <iostream>

void CreditManager::enqueue_report_event()
{
    if (enqueue_report_valid.read())
    {
        unsigned flow_id = 0;
        unsigned packet_size = 0;
        EnQueueReport report = enqueue_report.read();
        try
        {
            flow_id = report.get_flow_id();
            packet_size = report.get_packet_size();
            queue_size[flow_id] += packet_size;
            log.prefix() << "enqueue report event, flow id: " << flow_id << ", "
                         << "packet size: " << packet_size << "." << endl;
        }
        catch (Exception & e)
        {
            std::cout << "Exception:"
                      << " " << e.ToString() << std::endl
                      << "Stack:"
                      << " " << e.Stack() << std::endl;
        }
    }
}

void CreditManager::credit_apply()
{
    int last_apply = 0;
    for (;;)
    {
        flow_status_message_out_valid.write(false);
        unsigned apply_num = 0;
        for (int flow_id = (last_apply + 1) % CREDIT_MANAGER_QUEUE_NUM; apply_num < CREDIT_MANAGER_QUEUE_NUM;
             flow_id = (flow_id + 1) % CREDIT_MANAGER_QUEUE_NUM, apply_num++)
        {
            if (credit_balance[flow_id] >= 0)
            {
                continue;
            }
            else if (credit_balance[flow_id] < 0)
            {
                try
                {
                    flow_status_message_local.set_flow_id(flow_id);
                    flow_status_message_local.set_status(STATUS_NORMAL);
                    flow_status_message_local.set_dest_tm_id(DestinationTable::get_instance().get_dest_tm_id(flow_id));
                    flow_status_message_local.set_src_tm_id(_TM_ID_);
                    stat_counter.increase_counter("flow status msg",
                                                  DestinationTable::get_instance().get_dest_tm_id(flow_id), 1);
                    log.prefix() << "credit apply,"
                                 << " dest tm id: " << DestinationTable::get_instance().get_dest_tm_id(flow_id) << ", "
                                 << " flow id: " << flow_id << ", "
                                 << "status: "
                                 << "NORMAL"
                                 << "." << endl;
                }
                catch (Exception & e)
                {
                    std::cout << "Exception:"
                              << " " << e.ToString() << std::endl
                              << "Stack:"
                              << " " << e.Stack() << std::endl;
                }
                flow_status_message_out_valid.write(true);
                flow_status_message_out.write(flow_status_message_local);
                last_apply = flow_id;
                break;
            }
        }
        wait();
    }
}

void CreditManager::credit_accept()
{
    if (credit_info_in_valid.read())
    {
        CreditInfo info = credit_info_in.read();
        unsigned flow_id = -1;
        unsigned credit = 0;
        try
        {
            flow_id = info.get_flow_id();
            credit = info.get_credit();
            credit_balance[flow_id] += CREDIT_MANAGER_CREDIT_RESOLUTION_4 * credit;
            stat_counter.increase_counter("credit recv", 1);
            log.prefix() << "credit accept, flow id: " << flow_id << ", "
                         << "credit: " << credit << "." << endl;
        }
        catch (Exception & e)
        {
            std::cout << "Exception:"
                      << " " << e.ToString() << std::endl
                      << "Stack:"
                      << " " << e.Stack() << std::endl;
        }
    }
}

void CreditManager::dequeue_sch()
{
    int last_sch = 0;
    for (;;)
    {
        dequeue_command_valid.write(false);
        unsigned sch_num = 0;
        for (unsigned flow_id = (last_sch + 1) % CREDIT_MANAGER_QUEUE_NUM; sch_num < CREDIT_MANAGER_QUEUE_NUM;
             flow_id = (flow_id + 1) % CREDIT_MANAGER_QUEUE_NUM, sch_num++)
        {
            if (queue_size[flow_id] == 0)
            {
                continue;
            }
            else if (queue_size[flow_id] > 0 && credit_balance[flow_id] >= 0)
            {
                DeQueueCommand command;
                try
                {
                    command.set_flow_id(flow_id);
                    dequeue_command.write(command);
                    dequeue_command_valid.write(true);
                    last_sch = flow_id;
                    log.prefix() << "dequeue sch, flow id: " << flow_id << ","
                                 << "credit banlance: " << credit_balance[flow_id] << "." << endl;
                    break;
                }
                catch (Exception & e)
                {
                    std::cout << "Exception:"
                              << " " << e.ToString() << std::endl
                              << "Stack:"
                              << " " << e.Stack() << std::endl;
                }
            }
        }
        wait();
    }
}

void CreditManager::dequeue_report_event()
{
    if (dequeue_report_valid.read())
    {
        unsigned flow_id = 0;
        unsigned packet_size = 0;
        DeQueueReport report = dequeue_report.read();
        try
        {
            flow_id = report.get_flow_id();
            packet_size = report.get_packet_size();
            queue_size[flow_id] -= packet_size;
            credit_balance[flow_id] -= packet_size;
            log.prefix() << "dequeue report event, flow id: " << flow_id << ", "
                         << "packet size: " << packet_size << ","
                         << "queue size: " << queue_size[flow_id] << ", "
                         << "credit banlance:" << credit_balance[flow_id] << "." << endl;
        }
        catch (Exception & e)
        {
            std::cout << "Exception:"
                      << " " << e.ToString() << std::endl
                      << "Stack:"
                      << " " << e.Stack() << std::endl;
        }
    }
}