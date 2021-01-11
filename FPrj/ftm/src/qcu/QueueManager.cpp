#include "QueueManager.h"
void QueueManager::recv_packet()
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

void QueueManager::recv_packet_descriptor()
{
    if (packet_descriptor_in_valid.read())
    {
        pd descriptor = packet_descriptor_in.read();
        packet_descriptor_in_fifo.push(packet_descriptor_in.read());
        log.prefix() << "recv pd." << endl;
    }
    if (packet_descriptor_in_fifo.get_size() >= PD_FIFO_SIZE - 1)
    {
        packet_descriptor_fc.write(true);
    }
    else
    {
        packet_descriptor_fc.write(false);
    }
    if (!packet_descriptor_in_fifo.is_empty())
    {
        packet_read.write(true);
        log.prefix() << "packet read signal set true" << std::endl;
    }
    else
    {
        packet_read.write(false);
    }
}

void QueueManager::filt()
{
    /*根据PD判断入队并存入缓存，向授权管理发送入队报告*/
    if (!packet_descriptor_in_fifo.is_empty() && !packet_in_fifo.is_empty())
    {
        pd packet_descriptor = packet_descriptor_in_fifo.pop();
        FPacket packet = packet_in_fifo.pop();
        FHeader ftmh = packet.get_ftmh();
        //丢包
        if (packet_descriptor.get_result())
        {
            //packet_in_fifo.pop();
            return;
        }
        //入队，FTMH头的src_tm_id存入查找到的dest_tm_id，存入缓存
        else
        {
            try
            {
                ftmh.set_src_tm_id(DestinationTable::get_instance().get_dest_tm_id(packet_descriptor.get_flowID()));
                packet.set_ftmh(ftmh);
                packet_out_fifo.push(packet);
                packet_descriptor_process_fifo.push(packet_descriptor);
                log.prefix() << "saving,"
                             << " "
                             << "flow id:" << packet_descriptor.get_flowID() << ","
                             << " "
                             << "packet in fifo size:"
                             << " " << packet_in_fifo.get_size() << "." << std::endl;
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

void QueueManager::enqueue()
{
    this->enqueue_report_out_valid.write(false);
    EnQueueReport enqueue_report;
    pd packet_descriptor;
    /*将PD放入对应队列*/
    if (addr_in_valid.read())
    {
        unsigned flow_id = 0;
        unsigned packet_size = 0;
        if (packet_descriptor_process_fifo.is_empty())
        {
            throw Exception("error : packet_descriptor_process_fifo is empty.");
        }
        try
        {
            packet_descriptor = packet_descriptor_process_fifo.pop();
            packet_descriptor.set_addr(addr_in.read());
            flow_id = packet_descriptor.get_flowID();
            packet_size = packet_descriptor.get_length();
            queues[flow_id].push(packet_descriptor);
            queue_sizes[flow_id] += packet_size;
            enqueue_report.set_flow_id(flow_id);
            enqueue_report.set_packet_size(packet_size);
            this->enqueue_report_out.write(enqueue_report);
            this->enqueue_report_out_valid.write(true);
            log.prefix() << "enqueue, "
                         << "flow id:" << packet_descriptor.get_flowID() << "." << endl;
            stat_counter.increase_counter("enqueue", flow_id, 1);
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

void QueueManager::trans_packet()
{
    for (;;)
    {
        std::string packetBytes;
        if (packet_out_fifo.is_empty())
        {
            wait();
            continue;
        }
        try
        {
            packetBytes = packet_out_fifo.pop().get_bytes();
        }
        catch (Exception & e)
        {
            std::cout << "Exception:"
                      << " " << e.ToString() << std::endl
                      << "Stack:"
                      << " " << e.Stack() << std::endl;
        }
        trs.transmit_to_end(packetBytes.data(), packetBytes.size());
    }
}

void QueueManager::dequeue()
{
    addr_out_valid.write(false);
    dequeue_report_to_cm_out_valid.write(false);
    dequeue_report_to_cavd_out_valid.write(false);
    if (dequeue_command_in_valid.read())
    {
        DeQueueCommand command = dequeue_command_in.read();
        DeQueueReport report;
        pd packet_descriptor;
        if (!queues[command.get_flow_id()].empty())
        {
            try
            {
                packet_descriptor = queues[command.get_flow_id()].front();
                queues[command.get_flow_id()].pop();
                addr_out.write(packet_descriptor.get_addr());
                addr_out_valid.write(true);
                report.set_flow_id(command.get_flow_id());
                report.set_packet_size(packet_descriptor.get_length());
                dequeue_report_to_cm_out.write(report);
                dequeue_report_to_cm_out_valid.write(true);
                dequeue_report_to_cavd_out.write(report);
                dequeue_report_to_cavd_out_valid.write(true);
                log.prefix() << "dequeue, "
                             << "flow id:" << packet_descriptor.get_flowID() << ", "
                             << "packet size: " << packet_descriptor.get_length() << "." << endl;
                stat_counter.increase_counter("dequeue", command.get_flow_id(), 1);
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
