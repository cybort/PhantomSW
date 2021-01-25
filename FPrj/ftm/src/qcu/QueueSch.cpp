/*
 * @Author: your name
 * @Date: 2021-01-18 09:47:07
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-22 11:44:08
 * @Description: file content
 */
#include "QueueSch.h"

void QueueSch::sch_queueing(unsigned flow_id)
{
    if ((queue_size[flow_id] > 0) && (credit_balance[flow_id] > 0) && (!sch_queueing_list[flow_id]))
    {
        QueuePriority queue_priority = queue_priority_list[flow_id];
        switch (queue_priority)
        {
        case H_MULTICAST:
            high_priority_multicast.push(flow_id);
            sch_queueing_list[flow_id] = true;
            counter.increase_counter("sch_queueing_size", H_MULTICAST, 1);
            log.prefix() << "flow id: " << flow_id << " queueing H_MULTICAST." << std::endl;
            break;
        case L_MULTICAST:
            low_priority_multicast.push(flow_id);
            sch_queueing_list[flow_id] = true;
            counter.increase_counter("sch_queueing_size", L_MULTICAST, 1);
            log.prefix() << "flow id: " << flow_id << " queueing L_MULTICAST." << std::endl;
            break;
        case H_LOCAL_UNICAST:
            high_priority_local_unicast.push(flow_id);
            sch_queueing_list[flow_id] = true;
            counter.increase_counter("sch_queueing_size", H_LOCAL_UNICAST, 1);
            log.prefix() << "flow id: " << flow_id << " queueing H_LOCAL_UNICAST." << std::endl;
            break;
        case L_LOCAL_UNICAST:
            low_priority_local_unicast.push(flow_id);
            sch_queueing_list[flow_id] = true;
            counter.increase_counter("sch_queueing_size", L_LOCAL_UNICAST, 1);
            log.prefix() << "flow id: " << flow_id << " queueing L_LOCAL_UNICAST." << std::endl;
            break;
        case H_REMOTE_UNICAST:
            high_priority_remote_unicast.push(flow_id);
            sch_queueing_list[flow_id] = true;
            counter.increase_counter("sch_queueing_size", H_REMOTE_UNICAST, 1);
            log.prefix() << "flow id: " << flow_id << " queueing H_REMOTE_UNICAST." << std::endl;
            break;
        case L_REMOTE_UNICAST:
            low_priority_remote_unicast.push(flow_id);
            sch_queueing_list[flow_id] = true;
            counter.increase_counter("sch_queueing_size", L_REMOTE_UNICAST, 1);
            log.prefix() << "flow id: " << flow_id << " queueing L_REMOTE_UNICAST." << std::endl;
            break;
        default:
            throw Exception("error: queue priority not found!");
            break;
        }
    }
}

void QueueSch::request_rcev()
{
    EnQueueReport en_queue_report;
    DeQueueReport de_queue_report;
    CreditInfo credit_info;
    if (en_queue_report_in_valid.read())
    {
        en_queue_report = en_queue_report_in.read();
        this->queue_size[en_queue_report.get_flow_id()]++;
        counter.increase_counter("queue_size", en_queue_report.get_flow_id(), 1);
        log.prefix() << "recv en_queue_report,flow id :" << en_queue_report.get_flow_id()
                     << ", packet_size: " << en_queue_report.get_packet_size()
                     << ", queue_size: " << queue_size[en_queue_report.get_flow_id()] << "." << std::endl;
        //排队过滤，不在排队的队列才能触发
        if (!sch_queueing_list[en_queue_report.get_flow_id()])
        {
            en_queue_report_fifo.push(en_queue_report.get_flow_id());
        }
    }
    if (credit_info_in_valid.read())
    {
        credit_info = credit_info_in.read();
        this->credit_balance[credit_info.get_flow_id()] += credit_info.get_credit();
        write_request_fifo.push(credit_info.get_flow_id());
        counter.increase_counter("credit_balance", credit_info.get_flow_id(), credit_info.get_credit());
        log.prefix() << "recv credit_info." << std::endl;
    }
    else if (!en_queue_report_fifo.is_empty())
    {
        write_request_fifo.push(en_queue_report_fifo.pop());
    }
    if (de_queue_report_in_valid.read())
    {
        de_queue_report = de_queue_report_in.read();
        this->credit_balance[de_queue_report.get_flow_id()] -= de_queue_report.get_packet_size();
        read_request_fifo.push(de_queue_report.get_flow_id());
        counter.increase_counter("credit_balance", de_queue_report.get_flow_id(), -de_queue_report.get_packet_size());
        log.prefix() << "recv de_queue_report." << std::endl;
    }
}

void QueueSch::sch_queueing_trigger()
{
    bool last_request_read = false;
    for (;;)
    {
        if ((!write_request_fifo.is_empty()) && (!read_request_fifo.is_empty()))
        {
            if (last_request_read)
            {
                sch_queueing(write_request_fifo.pop());
                last_request_read = false;
                log.prefix() << "queue schedule queueing trigger by write request." << std::endl;
            }
            else
            {
                sch_queueing(read_request_fifo.pop());
                last_request_read = true;
                log.prefix() << "queue schedule queueing trigger by read request." << std::endl;
            }
        }
        else if (!write_request_fifo.is_empty())
        {
            sch_queueing(write_request_fifo.pop());
            last_request_read = false;
            log.prefix() << "queue schedule queueing trigger by write request." << std::endl;
        }
        else if (!read_request_fifo.is_empty())
        {
            sch_queueing(read_request_fifo.pop());
            last_request_read = true;
            log.prefix() << "queue schedule queueing trigger by read request." << std::endl;
        }
        wait();
    }
}

void QueueSch::clos_sch()
{

    char last_sch = 0;
    DeQueueCommand de_queue_command;
    unsigned flow_id = -1;
    for (;;)
    {
        char round_robin_count = 0;
        de_queue_command_out_valid.write(false);
        for (char round_robin_param = (last_sch + 1) % 3; round_robin_count < 3;
             round_robin_param = (round_robin_param + 1) % 3, round_robin_count++)
        {
            if (round_robin_param == 0)
            {
                if (!high_priority_multicast.is_empty())
                {
                    flow_id = high_priority_multicast.pop();
                    this->queue_size[flow_id]--;
                    de_queue_command.set_flow_id(flow_id);
                    de_queue_command_out.write(de_queue_command);
                    de_queue_command_out_valid.write(true);
                    sch_queueing_list[flow_id] = false;
                    last_sch = 0;
                    counter.increase_counter("queue_size", flow_id, -1);
                    counter.increase_counter("sch_queueing_size", H_MULTICAST, 1);
                    log.prefix() << "dequeue schedule,flow id: " << flow_id << "." << std::endl;
                    break;
                }
                else if (!low_priority_multicast.is_empty())
                {
                    flow_id = low_priority_multicast.pop();
                    this->queue_size[flow_id]--;
                    de_queue_command.set_flow_id(flow_id);
                    de_queue_command_out.write(de_queue_command);
                    de_queue_command_out_valid.write(true);
                    sch_queueing_list[flow_id] = false;
                    last_sch = 0;
                    counter.increase_counter("queue_size", flow_id, -1);
                    counter.increase_counter("sch_queueing_size", L_MULTICAST, 1);
                    log.prefix() << "dequeue schedule,flow id: " << flow_id << "." << std::endl;
                    break;
                }
            }
            if (round_robin_param == 1)
            {
                if (!high_priority_local_unicast.is_empty())
                {
                    flow_id = high_priority_local_unicast.pop();
                    this->queue_size[flow_id]--;
                    de_queue_command.set_flow_id(flow_id);
                    de_queue_command_out.write(de_queue_command);
                    de_queue_command_out_valid.write(true);
                    sch_queueing_list[flow_id] = false;
                    last_sch = 1;
                    counter.increase_counter("queue_size", flow_id, -1);
                    counter.increase_counter("sch_queueing_size", H_LOCAL_UNICAST, 1);
                    log.prefix() << "dequeue schedule,flow id: " << flow_id << "." << std::endl;
                    break;
                }
                else if (!low_priority_local_unicast.is_empty())
                {
                    flow_id = low_priority_local_unicast.pop();
                    this->queue_size[flow_id]--;
                    de_queue_command.set_flow_id(flow_id);
                    de_queue_command_out.write(de_queue_command);
                    de_queue_command_out_valid.write(true);
                    sch_queueing_list[flow_id] = false;
                    last_sch = 1;
                    counter.increase_counter("queue_size", flow_id, -1);
                    counter.increase_counter("sch_queueing_size", L_LOCAL_UNICAST, 1);
                    log.prefix() << "dequeue schedule,flow id: " << flow_id << "." << std::endl;
                    break;
                }
            }
            if (round_robin_param == 2)
            {
                if (!high_priority_remote_unicast.is_empty())
                {
                    flow_id = high_priority_remote_unicast.pop();
                    this->queue_size[flow_id]--;
                    de_queue_command.set_flow_id(flow_id);
                    de_queue_command_out.write(de_queue_command);
                    de_queue_command_out_valid.write(true);
                    sch_queueing_list[flow_id] = false;
                    last_sch = 2;
                    counter.increase_counter("queue_size", flow_id, -1);
                    counter.increase_counter("sch_queueing_size", H_REMOTE_UNICAST, -1);
                    log.prefix() << "dequeue schedule,flow id: " << flow_id << "." << std::endl;
                    break;
                }
                else if (!low_priority_local_unicast.is_empty())
                {
                    flow_id = low_priority_remote_unicast.pop();
                    this->queue_size[flow_id]--;
                    de_queue_command.set_flow_id(flow_id);
                    de_queue_command_out.write(de_queue_command);
                    de_queue_command_out_valid.write(true);
                    sch_queueing_list[flow_id] = false;
                    last_sch = 2;
                    counter.increase_counter("queue_size", flow_id, -1);
                    counter.increase_counter("sch_queueing_size", L_REMOTE_UNICAST, 1);
                    log.prefix() << "dequeue schedule,flow id: " << flow_id << "." << std::endl;
                    break;
                }
            }
        }
        wait();
    }
}