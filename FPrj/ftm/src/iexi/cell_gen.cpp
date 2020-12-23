#include "cell_gen.h"
#include "crc.h"
#include "port.h"

void cell_gen::recv()
{
    while (true)
    {
        rc.receive_to_end();
        pkt_q.push(rc.result());
        wait();
    }
}

void cell_gen::split()
{
    std::string s;
    while (pkt_q.pop_if_not_empty(s))
    {
        int start = 0;
        int cell_num = 0;
        FPacket current_packet;
        current_packet.set_bytes(s);

        FHeader current_header = current_packet.get_ftmh();

        int dest_id = current_header.get_src_tm_id(); // dest cache in src field

        current_header.set_src_tm_id(SRC_TM_ID);
        current_packet.set_ftmh(current_header);
        s = current_packet.get_bytes();
        int length = s.size();

        while (length > 0)
        {
            if (length > PKT_DATA_BANDWIDTH + MIN_CELL)
            {
                cell c;
                fill_cell(c, s.c_str() + start, 64, dest_id);
                c.eop = false;
                cell_q.push(c);
                start += 64;
                length -= 64;

                fill_cell(c, s.c_str() + start, 96, dest_id);
                c.eop = false;
                start += 96;
                length -= 96;
                cell_q.push(c);

                cell_num += 2;
            }
            else
            {
                if (length > MID_CELL)
                {
                    cell c;
                    fill_cell(c, s.c_str() + start, 64, dest_id);
                    c.eop = false;
                    cell_q.push(c);
                    start += 64;
                    length -= 64;

                    cell_num++;

                    /*fill_cell(c, s.c_str()+start, length, dest_id);
                    c.eop = true;
                    cell_q.push(c);
                    start+=length;
                    length-=length;

                    cell_num+=2;*/
                }
                else
                {
                    cell c;
                    fill_cell(c, s.c_str() + start, length, dest_id);
                    c.eop = true;
                    cell_q.push(c);
                    start += length;
                    length -= length;

                    cell_num++;
                }
            }
            if (length == 0)
                cell_num_q.push(cell_num);
        }
    }
}

cell & cell_gen::fill_cell(cell & c, const char * str, int str_size, int dest_id)
{
    memcpy(c.data, str, str_size);
    c.len = str_size;
    c.cell_type(CellType::Unicast);
    c.source_id(SRC_TM_ID);
    c.dest_id(dest_id);
    if (debug)
    {
        log.prefix() << "fill cell length:" << c.len << endl;
    }
    return c;
}

void cell_gen::transfer()
{
    if (cell_num_remain <= 0) /*not sending long packet*/
    {
        int cell_num = 0;
        cell_num_q.pop_if_not_empty(cell_num);
        cell_num_remain = cell_num;
        current_seq = 0;
        current_t = timeslot;
    }

    int i;
    for (i = 0; i < TM_CELL_PER_CLOCK_LIMIT && cell_num_remain > 0; i++, cell_num_remain--)
    {
        cell c;
        if (!cell_q.pop_if_not_empty(c))
        {
            if (debug)
            {
                log.prefix() << "No cell to send! current_t:" << current_t << " current_seq:" << current_seq
                             << " cell_num_remain:" << cell_num_remain << std::endl;
            }
        }
        c.packet_id(current_t);
        c.cell_id(current_seq);
        c.refresh_crc();
        current_seq++;
        /*c.data...*/
        valid[i].write(true);
        data[i].write(c);
        if (debug)
        {
            c.dump_header("cell_gen transfer", log.prefix());
        }
    }
    /*send empty cell for remain idle signal*/
    for (; i < TM_CELL_PER_CLOCK_LIMIT; i++)
    {
        cell c;
        c.packet_id(timeslot);
        c.cell_id(0);
        c.set_empty();
        valid[i].write(true);
        data[i].write(c);
        if (debug)
        {
            // c.dump_header("cell_gen trans empty", log.prefix());
        }
    }
    timeslot = (timeslot + 1) % 0xFFFFFF;
}

void cell_gen::update_counter()
{
    stat.update_counter("packet_waiting_split", pkt_q.size());
    stat.update_counter("cell_waiting_transfer", cell_q.size());
    stat.update_counter("cell_waiting_transfer_by_packets", cell_num_q.size());
}
