/*
 * @Author: your name
 * @Date: 2021-01-19 10:56:15
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-22 14:30:31
 * @Description: file content
 */
#include "CreditManager.h"

void CreditManager::recv_request()
{
    EnQueueReport en_queue_report;
    DeQueueReport de_queue_report;
    CreditInfo credit_info;
    if (en_queue_report_in_valid.read())
    {
        en_queue_report = en_queue_report_in.read();
        this->queue_size[en_queue_report.get_flow_id()] += en_queue_report.get_packet_size();
        log.prefix() << "recv en_queue_report,flow_id: " << en_queue_report.get_flow_id() << std::endl;
        if (en_queue_report.get_flow_id() >= 4)
        {
            en_queue_report_fifo.push(en_queue_report.get_flow_id());
        }
    }
    if (credit_info_in_valid.read())
    {
        credit_info = credit_info_in.read();
        this->credit_balance[credit_info.get_flow_id()] += credit_info.get_credit();
        log.prefix() << "recv credit_info,flow_id: " << en_queue_report.get_flow_id() << std::endl;
        if (credit_info.get_flow_id() >= 4)
        {
            write_request_fifo.push(credit_info.get_flow_id());
        }
    }
    else if (!en_queue_report_fifo.is_empty())
    {
        write_request_fifo.push(en_queue_report_fifo.pop());
    }
    if (de_queue_report_in_valid.read())
    {
        de_queue_report = de_queue_report_in.read();
        this->queue_size[de_queue_report.get_flow_id()] -= de_queue_report.get_packet_size();
        this->credit_balance[de_queue_report.get_flow_id()] -= de_queue_report.get_packet_size();
        log.prefix() << "recv de_queue_report,flow_id: " << de_queue_report.get_flow_id() << std::endl;
        if (de_queue_report.get_flow_id() >= 4)
        {
            read_request_fifo.push(de_queue_report.get_flow_id());
        }
    }
}

void CreditManager::crs_state_machine(unsigned flow_id)
{
    FlowStatusMessage flow_status_message;
    flow_status_message.set_flow_id(flow_id);
    flow_status_message.set_src_tm_id(_TM_ID_);
    flow_status_message.set_dest_tm_id(DestinationTable::get_instance().get_dest_tm_id(flow_id));
    if (old_crs[flow_id] == STATUS_OFF)
    {

        if (queue_size[flow_id] > 0)
        {

            if (credit_balance[flow_id] < BACK_OFF_EXIT_TH)
            {
                if (credit_balance[flow_id] - queue_size[flow_id] < BACK_LOG_OFF_EXIT_TH)
                {
                    if (queue_size[flow_id] - credit_balance[flow_id] > OFF_TO_NORMAL_TH)
                    {

                        flow_status_message.set_status(STATUS_NORMAL);
                    }
                    else
                    {
                        if (queue_size[flow_id] - credit_balance[flow_id] > OFF_TO_SLOW_TH)
                        {

                            flow_status_message.set_status(STATUS_SLOW);
                        }
                        else
                        {
                            flow_status_message.set_status(STATUS_OFF);
                        }
                    }
                }
                else
                {
                    flow_status_message.set_status(STATUS_OFF);
                }
            }
            else
            {
                flow_status_message.set_status(STATUS_OFF);
            }
        }
        else
        {
            flow_status_message.set_status(STATUS_OFF);
        }
    }
    if (old_crs[flow_id] == STATUS_SLOW)
    {
        if (queue_size[flow_id] - credit_balance[flow_id] > SLOW_TO_NORMAL_TH)
        {
            flow_status_message.set_status(STATUS_NORMAL);
        }
        else
        {
            if (queue_size[flow_id] == 0)
            {
                if (credit_balance[flow_id] >= EMPTY_CREDIT_TH)
                {
                    flow_status_message.set_status(STATUS_OFF);
                }
                else
                {
                    flow_status_message.set_status(STATUS_SLOW);
                }
            }
            else
            {
                if (credit_balance[flow_id] - queue_size[flow_id] >= BACK_LOG_OFF_TH)
                {
                    flow_status_message.set_status(STATUS_OFF);
                }
                else
                {
                    if (credit_balance[flow_id] >= BACK_OFF_TH)
                    {
                        flow_status_message.set_status(STATUS_OFF);
                    }
                    else
                    {
                        flow_status_message.set_status(STATUS_SLOW);
                    }
                }
            }
        }
    }
    if (old_crs[flow_id] == STATUS_NORMAL)
    {
        if (queue_size[flow_id] - credit_balance[flow_id] < NORMAL_TO_SLOW_TH)
        {
            flow_status_message.set_status(STATUS_SLOW);
        }
        else
        {
            if (queue_size[flow_id] == 0)
            {
                if (credit_balance[flow_id] >= EMPTY_CREDIT_TH)
                {
                    flow_status_message.set_status(STATUS_OFF);
                }
                else
                {
                    flow_status_message.set_status(STATUS_NORMAL);
                }
            }
            else
            {
                if (credit_balance[flow_id] - queue_size[flow_id] >= BACK_LOG_OFF_TH)
                {
                    flow_status_message.set_status(STATUS_OFF);
                }
                else
                {
                    if (credit_balance[flow_id] >= BACK_OFF_TH)
                    {
                        flow_status_message.set_status(STATUS_OFF);
                    }
                    else
                    {
                        flow_status_message.set_status(STATUS_NORMAL);
                    }
                }
            }
        }
    }

    log.prefix() << "generate flow status message, flow_id: " << flow_id
                 << ", status: " << flow_status_message.get_status() << "." << std::endl;
    //同状态过滤
    if (flow_status_message.get_status() != old_crs[flow_id])
    {
        old_crs[flow_id] = flow_status_message.get_status();
        flow_status_message_fifo.push(flow_status_message);
        log.prefix() << "crs filt, put flow status message in fifo, flow_id: " << flow_id
                     << " ,flow_status: " << flow_status_message.get_status() << "." << std::endl;
    }
    //后续删除else中发送的代码，目前收到请求发送一个credit.
    else
    {
        old_crs[flow_id] = flow_status_message.get_status();
        flow_status_message_fifo.push(flow_status_message);
        log.prefix() << "same status, flow_id: " << flow_id << " ,flow_status: " << flow_status_message.get_status()
                     << "." << std::endl;
    }
}

void CreditManager::multicast_credit_generator()
{
    char clk_count = 0;
    CreditInfo creidt_info;
    for (;;)
    {
        if (clk_count < 1)
        {
            if (queue_size[0] > 0)
            {
                creidt_info.set_flow_id(0);
                creidt_info.set_credit(60);
                multicast_credit_fifo.push(creidt_info);
                clk_count++;
                log.prefix() << "generate mc credit for flow 0 " << std::endl;
            }
            else if (queue_size[1] > 0)
            {
                creidt_info.set_flow_id(1);
                creidt_info.set_credit(60);
                multicast_credit_fifo.push(creidt_info);
                log.prefix() << "generate mc credit for flow 1 " << std::endl;
                clk_count++;
            }
            else if (queue_size[2] > 0)
            {
                creidt_info.set_flow_id(2);
                creidt_info.set_credit(60);
                multicast_credit_fifo.push(creidt_info);
                log.prefix() << "generate mc credit for flow 2 " << std::endl;
                clk_count++;
            }
            else if (queue_size[3] > 0)
            {
                creidt_info.set_flow_id(3);
                creidt_info.set_credit(60);
                multicast_credit_fifo.push(creidt_info);
                log.prefix() << "generate mc credit for flow 3 " << std::endl;
                clk_count++;
            }
        }
        else
        {
            clk_count = 0;
        }
        wait();
    }
}

void CreditManager::crs_state_machine_trigger()
{
    bool last_request_read = false;
    for (;;)
    {
        if ((!write_request_fifo.is_empty()) && (!read_request_fifo.is_empty()))
        {
            if (last_request_read)
            {
                crs_state_machine(write_request_fifo.pop());
                last_request_read = false;
            }
            else
            {
                crs_state_machine(read_request_fifo.pop());
                last_request_read = true;
            }
        }
        else if (!write_request_fifo.is_empty())
        {
            crs_state_machine(write_request_fifo.pop());
            last_request_read = false;
        }
        else if (!read_request_fifo.is_empty())
        {
            crs_state_machine(read_request_fifo.pop());
            last_request_read = true;
        }
        wait();
    }
}

void CreditManager::trans_fsm()
{
    FlowStatusMessage flow_status_message;
    flow_status_message_out_valid.write(false);
    if (!flow_status_message_fifo.is_empty())
    {
        flow_status_message = flow_status_message_fifo.pop();
        flow_status_message_out.write(flow_status_message);
        flow_status_message_out_valid.write(true);
        log.prefix() << "send flow status message, flow_id: " << flow_status_message.get_flow_id()
                     << ", status: " << flow_status_message.get_status() << "." << std::endl;
    }
}

void CreditManager::trans_credit()
{
    bool last_credit_unicast = false;
    CreditInfo credit_info;
    for (;;)
    {
        credit_info_out_valid.write(false);
        if (last_credit_unicast)
        {
            if (!multicast_credit_fifo.is_empty())
            {
                credit_info = multicast_credit_fifo.pop();
                credit_info_out.write(credit_info);
                credit_info_out_valid.write(true);
                last_credit_unicast = false;
                log.prefix() << "send mc credit " << std::endl;
            }
            else if (!unicast_credit_fifo.is_empty())
            {
                credit_info = unicast_credit_fifo.pop();
                credit_info_out.write(credit_info);
                credit_info_out_valid.write(true);
                last_credit_unicast = true;
            }
        }
        else
        {
            if (!unicast_credit_fifo.is_empty())
            {
                credit_info = unicast_credit_fifo.pop();
                credit_info_out.write(credit_info);
                credit_info_out_valid.write(true);
                last_credit_unicast = true;
            }
            else if (!multicast_credit_fifo.is_empty())
            {
                credit_info = multicast_credit_fifo.pop();
                credit_info_out.write(credit_info);
                credit_info_out_valid.write(true);
                last_credit_unicast = false;
            }
        }
        wait();
    }
}

void CreditManager::recv_credit()
{
    CreditInfo credit_info;
    if (credit_info_in_valid.read())
    {
        credit_info = credit_info_in.read();
        unicast_credit_fifo.push(credit_info);
    }
}
