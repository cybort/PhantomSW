/*
 * @Author: your name
 * @Date: 2021-01-13 13:37:07
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-22 14:04:16
 * @Description: file content
 */
#include "EnQueueProcessor.h"

void EnQueueProcessor::recv_packet()
{
    for (;;)
    {
        FPacket packet;
        recv.receive_to_end();
        try
        {
            packet.set_bytes(recv.result());
        }
        catch (Exception & e)
        {
            std::cout << "Exception:"
                      << " " << e.ToString() << std::endl
                      << "Stack:"
                      << " " << e.Stack() << std::endl;
        }
        log.prefix() << "recv packet." << endl;
        packet_in_fifo.push(packet);
        wait();
    }
}

void EnQueueProcessor::recv_packet_descriptor()
{
    if (packet_descriptor_in_valid.read())
    {
        pd descriptor = packet_descriptor_in.read();
        packet_descriptor_in_fifo.push(packet_descriptor_in.read());
        log.prefix() << "Recv PD" << endl;
    }
    if (packet_descriptor_in_fifo.get_size() >= packet_descriptor_in_fifo.get_max_size() - 1)
    {
        packet_descriptor_fc.write(true);
        log.prefix() << "PD FIFO is full, PD FC set true." << endl;
    }
    else
    {
        packet_descriptor_fc.write(false);
    }
    if (!packet_descriptor_in_fifo.is_empty())
    {
        packet_read.write(true);
        log.prefix() << "Packet read signal set true" << std::endl;
    }
    else
    {
        packet_read.write(false);
    }
}

void EnQueueProcessor::process()
{
    /*根据PD判断入队并存入缓存，向授权管理和队列调度发送入队报告*/
    if (!packet_descriptor_in_fifo.is_empty() && !packet_in_fifo.is_empty())
    {
        pd packet_descriptor = packet_descriptor_in_fifo.pop();
        FPacket packet = packet_in_fifo.pop();
        FHeader ftmh = packet.get_ftmh();
        //丢包
        if (packet_descriptor.get_result())
        {
            return;
        }
        //入队，FTMH头的src_tm_id存入查找到的dest_tm_id，存入缓存
        else
        {
            try
            {
                unsigned logic_addr = 0;
                ftmh.set_src_tm_id(DestinationTable::get_instance().get_dest_tm_id(packet_descriptor.get_flowID()));
                packet.set_ftmh(ftmh);
                //查询逻辑地址
                for (logic_addr = 0; logic_addr < PACKET_NUM_MAX; logic_addr++)
                {
                    if (LogicAddrTable::get_instance().get_addr_status(logic_addr))
                    {
                        if (logic_addr == PACKET_NUM_MAX - 1)
                        {
                            throw Exception("error: Memory is full!");
                        }
                        continue;
                    }
                    else
                    {
                        LogicAddrTable::get_instance().set_addr_status(logic_addr, true);
                        break;
                    }
                }
                packet_descriptor.set_addr(logic_addr);
                logic_addr_out_fifo.push(logic_addr);
                packet_out_fifo.push(packet);
                packet_descriptor_out_fifo.push(packet_descriptor);
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
}

void EnQueueProcessor::trans_packet()
{
    for (;;)
    {
        std::string packetBytes;
        unsigned logic_addr = 0;
        if (packet_out_fifo.is_empty())
        {
            wait();
            continue;
        }
        try
        {
            packetBytes = packet_out_fifo.pop().get_bytes();
            logic_addr = logic_addr_out_fifo.pop();
        }
        catch (Exception & e)
        {
            std::cout << "Exception:"
                      << " " << e.ToString() << std::endl
                      << "Stack:"
                      << " " << e.Stack() << std::endl;
        }
        logic_addr_out.write(logic_addr);
        trs.transmit_to_end(packetBytes.data(), packetBytes.size());
    }
}

void EnQueueProcessor::trans_packet_descriptor()
{
    EnQueueReport en_queue_report;
    pd packet_descriptor;
    unsigned flow_id = 0;
    unsigned packet_size = 0;
    this->packet_descriptor_out_valid.write(false);
    /*收到写完成信号后，将PD发到队列链表管理模块，并生成入队报告放入FIFO*/
    if (write_packet_complete_signal_in.read())
    {
        if (packet_descriptor_out_fifo.is_empty())
        {
            throw Exception("error : packet_descriptor_process_fifo is empty.");
        }
        try
        {
            packet_descriptor = packet_descriptor_out_fifo.pop();
            flow_id = packet_descriptor.get_flowID();
            packet_size = packet_descriptor.get_length();
            en_queue_report.set_flow_id(flow_id);
            en_queue_report.set_packet_size(packet_size);
            this->en_queue_report_out_fifo.push(en_queue_report);
            this->packet_descriptor_out.write(packet_descriptor);
            this->packet_descriptor_out_valid.write(true);
            log.prefix() << "send packet descriptor , generate enqueue report, "
                         << "flow id:" << packet_descriptor.get_flowID() << "." << endl;
            stat_counter.increase_counter("enqueue_report_generate", flow_id, 1);
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

void EnQueueProcessor::trans_en_queue_report()
{
    this->enqueue_report_to_credit_manager_out_valid.write(false);
    this->enqueue_report_to_queue_sch_out_valid.write(false);
    EnQueueReport en_queue_report;
    if (write_packet_descriptor_complete_signal_in.read())
    {
        if (en_queue_report_out_fifo.is_empty())
        {
            throw Exception("error : en_queue_report_out_fifo is empty.");
        }
        en_queue_report = en_queue_report_out_fifo.pop();
        this->enqueue_report_to_credit_manager_out.write(en_queue_report);
        this->enqueue_report_to_credit_manager_out_valid.write(true);
        this->enqueue_report_to_queue_sch_out.write(en_queue_report);
        this->enqueue_report_to_queue_sch_out_valid.write(true);
        log.prefix() << "send enqueue report." << endl;
    }
}
