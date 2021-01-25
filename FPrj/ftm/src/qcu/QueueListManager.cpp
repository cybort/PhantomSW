/*
 * @Author: your name
 * @Date: 2021-01-20 14:39:54
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-22 10:58:28
 * @Description: file content
 */
#include "QueueListManager.h"

void QueueListManager::en_queue()
{
    pd packet_descriptor;
    unsigned flow_id = -1;
    save_packet_descriptor_complete_signal_out.write(false);
    if (packet_descriptor_in_valid.read())
    {
        packet_descriptor = packet_descriptor_in.read();
        flow_id = packet_descriptor.get_flowID();
        virtual_output_queues[flow_id].push(packet_descriptor);
        save_packet_descriptor_complete_signal_out.write(true);
        log.prefix() << "enqueue,write packet descriptor,flow id: " << flow_id << ", "
                     << "addr: " << packet_descriptor.get_addr() << std::endl;
    }
}

void QueueListManager::de_queue()
{
    pd packet_descriptor;
    unsigned flow_id = -1;
    packet_descriptor_out_valid.write(false);
    if (flow_id_in_valid.read())
    {
        flow_id = flow_id_in.read();
        packet_descriptor = virtual_output_queues[flow_id].front();
        virtual_output_queues[flow_id].pop();
        virtual_output_queues_reading[flow_id].push(packet_descriptor);
        packet_descriptor_out.write(packet_descriptor);
        packet_descriptor_out_valid.write(true);
        log.prefix() << "dequeue,write packet descriptor,flow id: " << flow_id << ", "
                     << "addr: " << packet_descriptor.get_addr() << "." << std::endl;
    }
}

void QueueListManager::release_packet_descriptor()
{
    unsigned flow_id = -1;
    if (flow_id_release_in_valid.read())
    {
        flow_id = flow_id_release_in.read();
        virtual_output_queues_reading[flow_id].pop();
    }
}