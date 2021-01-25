/*
 * @Author: your name
 * @Date: 2021-01-14 15:20:13
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-22 10:58:49
 * @Description: file content
 */

#include "BufferManager.h"

void BufferManager::recv_packet()
{
    for (;;)
    {
        FPacket packet;
        unsigned logic_addr = 0;
        if (packet_in_sop.read())
        {
            logic_addr = write_logic_addr_in.read();
            recv.receive_to_end();
        }
        else
        {
            wait();
            continue;
        }
        try
        {
            packet.set_bytes(recv.result());
            log.prefix() << "recv packet." << std::endl;
        }
        catch (Exception & e)
        {
            std::cout << "Exception:"
                      << " " << e.ToString() << std::endl
                      << "Stack:"
                      << " " << e.Stack() << std::endl;
        }
        this->write_logic_addr_in_fifo.push(logic_addr);
        this->packet_in_fifo.push(packet);
        wait();
    }
}

void BufferManager::save_packet()
{

    unsigned logic_addr = 0;
    write_complete_signal_out.write(false);
    if (!packet_in_fifo.is_empty() && !write_logic_addr_in_fifo.is_empty())
    {
        logic_addr = write_logic_addr_in_fifo.pop();
        if (dram.count(logic_addr))
        {
            throw Exception("error: logic addr is in use.");
        }
        dram[logic_addr] = packet_in_fifo.pop();
        write_complete_signal_out.write(true);
        log.prefix() << "write packet at addr " << logic_addr << "." << std::endl;
    }
}

void BufferManager::read_packet()
{
    FPacket packet;
    if (read_logic_addr_in_valid.read())
    {
        if (dram.count(read_logic_addr_in.read()))
        {
            packet = dram[read_logic_addr_in.read()];
            dram.erase(read_logic_addr_in.read());
            packet_out_fifo.push(packet);
            log.prefix() << "read packet, "
                         << "address: " << read_logic_addr_in.read() << "." << std::endl;
        }
        else
        {
            std::string estring = "error: logic addr:" + std::to_string(read_logic_addr_in.read()) + " is empty.";
            throw Exception(estring);
        }
    }
}

void BufferManager::trans_packet()
{
    std::string packet_bytes;
    for (;;)
    {
        read_complete_signal_out.write(false);
        if (!packet_out_fifo.is_empty())
        {
            FPacket packet = packet_out_fifo.pop();
            packet_bytes = packet.get_bytes();
            read_complete_signal_out.write(true);
            trs.transmit_to_end(packet_bytes.data(), packet_bytes.size());
        }
        else
        {
            wait();
        }
    }
}