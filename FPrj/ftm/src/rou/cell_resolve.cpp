/*
 * @Description:
 * @Author: f21538
 * @Date: 2020-11-27 18:12:15
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:25:58
 */
#include "cell_resolve.h"

void cell_resolve::verify()
{

    for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
    {
        if (valid[i].read() == true)
        {
            cell c = data[i].read();
            if (!c.verify_crc())
            {
                c.dump_header("CRC ERROR!", log.prefix());
            }
            else if (c.len < MIN_CELL)
            {
                c.dump_header("cell too short!", log.prefix());
            }
            else if (c.len > MAX_CELL)
            {
                c.dump_header("cell too long!", log.prefix());
            }
            else /*valid cell*/
            {
                c.dump_header("resolve: ", log.prefix());
                packet_identifer k;
                k.timeslot = c.fts;
                k.src = c.src;
                if (cell_cache.count(k) <= 0) /*queue don't exists*/
                {
                    cell_wait_queue q;
                    cell_cache.insert(std::pair<packet_identifer, cell_wait_queue>(k, q));
                }
                cell_cache[k].queue.insert(c);
                if (c.eop == true)
                {
                    cell_cache[k].eop = true;
                }
                cell_cache[k].recv_time = cur_time;
            }
        }
    }
}

void cell_resolve::rebuild()
{
    for (std::map<packet_identifer, cell_wait_queue>::iterator iter = cell_cache.begin(); iter != cell_cache.end();)
    {
        packet_identifer packet_des = iter->first;
        cell_wait_queue cells = iter->second;
        std::set<cell>::iterator end_i = cells.queue.end();
        end_i--;
        if (cells.eop == true && end_i->fseq == cells.queue.size() - 1) /*packet received completely*/
        {
            std::string cur_packet("");
            for (std::set<cell>::iterator iter_set = cells.queue.begin(); iter_set != cells.queue.end(); iter_set++)
            {
                cur_packet += std::string(iter_set->data, iter_set->len);
            }
            cell_cache.erase(iter++);
            log.prefix() << "rebuild complete packet id " << packet_des.timeslot << endl;
            // packet_queue.push(cur_packet);
            packet_wait_queue.push(packet_wait_item(packet_des, cur_time, cur_packet));
        }
        else
        {
            iter++;
        }
    }
}

void cell_resolve::clean()
{
    for (std::map<packet_identifer, cell_wait_queue>::iterator iter = cell_cache.begin(); iter != cell_cache.end();)
    {
        packet_identifer packet_des = iter->first;
        cell_wait_queue cells = iter->second;
        if (check_time_exceed(cells.recv_time, cell_resolve_wait_time)) /*packet timeout*/
        {
            log.prefix() << "timeout: packet id " << packet_des.timeslot << " src id " << packet_des.src << std::endl;
            for (std::set<cell>::iterator iter_set = cells.queue.begin(); iter_set != cells.queue.end(); iter_set++)
            {
                cell c = *iter_set;
                c.dump_header("check queue: ", log.prefix());
            }
            cell_cache.erase(iter++);
        }
        else
        {
            iter++;
        }
    }
    cur_time++;
}

void cell_resolve::transfer()
{
    tr.set_debug(true);
    while (true)
    {
        if (packet_wait_queue.empty()) /*no packet to transfer*/
        {
            wait();
        }
        else
        {
            if (!check_time_exceed(packet_wait_queue.top().enqueue_time,
                                   packet_wait_threshold)) /*packet didn't wait enough time*/
            {
                wait();
            }
            else if (!cell_cache.empty() &&
                     current_min_waiting_timeslot() <
                         packet_wait_queue.top().packet_des.timeslot) /*previous packet is still rebuilding*/
            {
                wait();
            }
            else
            {
                const packet_wait_item s = packet_wait_queue.top();
                packet_wait_queue.pop();
                tr.transmit_to_end(s.packet_str.data(), s.packet_str.size());
                log.prefix() << "send downside timeslot " << s.packet_des.timeslot << " size " << s.packet_str.size()
                             << endl;
            }
        }
    }
}

void cell_resolve::update_counter()
{
    stat.update_counter("packet_rebuild_queue_size", cell_cache.size());
    stat.update_counter("packet_reorder_queue_size", packet_wait_queue.size());
}

inline bool cell_resolve::check_time_exceed(int timestamp, int time_threshold)
{
    return (cur_time - timestamp > time_threshold ||
            (cur_time < timestamp && (INT_MAX - timestamp + cur_time) > time_threshold));
}

inline int cell_resolve::current_min_waiting_timeslot() { return cell_cache.begin()->first.timeslot; }