
#include "BufferManager.h"

void BufferManager::recvPacket()
{
    for (;;)
    {
        FPacket packet;
        recv.receive_to_end();
        try
        {
            packet.set_bytes(recv.result());
            log.prefix() << "recv packet." << std::endl;
        }
        catch (Exception &e)
        {
            std::cout << "Exception:"
                      << " " << e.ToString() << std::endl
                      << "Stack:"
                      << " " << e.Stack() << std::endl;
        }
        this->packet_in_fifo.push(packet);
        wait();
    }
}

void BufferManager::save()
{
    int last_save = 0;
    for (;;)
    {
        addr_out_valid.write(false);
        if (!packet_in_fifo.is_empty())
        {
            for (unsigned addr = (last_save + 1) % PACKET_NUM_MAX; addr != last_save;
                 addr = (addr + 1) % PACKET_NUM_MAX)
            {
                if (dram.size() == PACKET_NUM_MAX)
                {
                    break;
                }
                if (dram.count(addr))
                {
                    continue;
                }
                dram[addr] = packet_in_fifo.pop();
                last_save = addr;
                addr_out.write(addr);
                addr_out_valid.write(true);
                log.prefix() << "save packet, "
                             << "address: " << addr << "." << std::endl;
                break;
            }
        }
        wait();
    }
}

void BufferManager::read()
{
    FPacket packet;
    if (addr_in_valid.read())
    {
        if (dram.count(addr_in.read()))
        {
            packet = dram[addr_in.read()];
            // std::cout << "time stamp: " << sc_time_stamp();
            // std::cout << ", read pkt: ";
            packet.dump();
            dram.erase(addr_in.read());
            packet_out_fifo.push(packet);
            log.prefix() << "read packet, "
                         << "address: " << addr_in.read() << "." << std::endl;
        }
        else
        {
            std::cout << "address"
                      << " " << addr_in.read() << ": "
                      << " no data." << std::endl;
        }
    }
}

void BufferManager::transPacket()
{
    std::string packet_bytes;
    for (;;)
    {
        if (!packet_out_fifo.is_empty())
        {
            FPacket packet = packet_out_fifo.pop();
            packet_bytes = packet.get_bytes();
            std::cout << "transfer";
            packet.dump();
            trs.transmit_to_end(packet_bytes.data(), packet_bytes.size());
        }
        else
        {
            wait();
        }
    }
}