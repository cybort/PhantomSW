/*
 * @Description:
 * @Author: f21538
 * @Date: 2020-11-27 18:12:14
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-22 14:41:17
 */
#include "rx.h"

#include "ClientServerLong.h"
#include <ListenSocket.h>
#include <SocketHandler.h>

#define LISTEN_WINDOW_SIZE 10
#define QUEUE_SIZE 3

void rx::recv()
{
    sc_time period(1, SC_MS);
    ListenSocket<ServerSocketLong<cell, std::priority_queue<cell, std::vector<cell>, std::greater<cell> > > /**/> *
        sockets[LISTEN_SOCKETS_NUM];
    while (true)
    {
        try
        {
            for (int i = 0; i < LISTEN_SOCKETS_NUM; i++)
            {
                sockets[i] = new ListenSocket<
                    ServerSocketLong<cell, std::priority_queue<cell, std::vector<cell>, std::greater<cell> > > /**/>(h);
                if (sockets[i]->Bind(TM_BASE_SERVER_PORT + i, LISTEN_WINDOW_SIZE))
                {
                    exit(-1);
                }
                h.Add(sockets[i]);
                if (debug)
                {
                    log.prefix() << "rx:add socket" << i << std::endl;
                }
            }
        }
        catch (Exception & e)
        {
            std::cout << "Exception: " << e.ToString() << std::endl << "Stack: " << std::endl << e.Stack() << std::endl;
        }
        h.Select(0, 1);
        while (h.GetCount())
        {
            h.Select(0, 1);
            keeper.inc(period);
            if (keeper.need_sync())
                keeper.sync();
        }

        for (int i = 0; i < LISTEN_SOCKETS_NUM; i++)
        {
            delete sockets[i];
        }
        if (debug)
        {
            log.prefix() << " all sockets closed" << endl;
        }
        wait();
    }
}

void rx::classify()
{
    cell temp;
    while (h.pop_if_not_empty(temp))
    {
        // temp.dump_header("classify: ", log.prefix());
        switch (temp.type)
        {
        case CellType::Unicast:
        case CellType::Multicast:
        {
            if (temp.len == 0)
            {
                temp.dump(log.prefix());
            }
            else
            {
                transfer_queue.push(temp);
            }
            log.prefix() << "data cell received" << std::endl;
            break;
        }
        case CellType::FlowSts:
        {
            cell_flowsts cell_f;
            temp.extract(cell_f);
            flowsts_queue.push(cell_f);
            break;
        }
        case CellType::Credit:
        {
            cell_credit cell_c;
            temp.extract(cell_c);
            credit_queue.push(cell_c);
            break;
        }
        default:
            std::cout << "type:" << temp.type << " error." << std::endl;
        }
    }
}

void rx::sch()
{
    cell temp;
    int cell_per_clock_limit = TM_CELL_PER_CLOCK_LIMIT;
    for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
    {
        if (transfer_queue.size() > 0 && transfer_queue.pop_if_not_empty(temp))
        {
            valid[i].write(true);
            data[i].write(temp);
            if (debug)
            {
                temp.dump_header("rx:received", log.prefix());
            }
        }
        else
        {
            valid[i].write(false);
        }
    }
}

void rx::ctrl_info()
{
    cell_flowsts temp_flowsts;
    if (flowsts_queue.pop_if_not_empty(temp_flowsts))
    {
        temp_flowsts.dump_header("rx:", log.prefix());
        if (check_request_sequence(temp_flowsts.source_id(), temp_flowsts.flow_id(), temp_flowsts.request_id()))
        {
            FlowStatusMessage status;
            status.set_flow_id(temp_flowsts.flow_id());
            status.set_status((CreditRequestStatus)temp_flowsts.request());
            status.set_dest_tm_id(temp_flowsts.dest_id());
            status.set_src_tm_id(temp_flowsts.source_id());
            flow_status_out.write(status);
            valid_flow_status_out.write(true);
            stat.increase_counter("flow_status_rx", temp_flowsts.dest_id(), 1);
        }
    }
    else
    {
        valid_flow_status_out.write(false);
    }

    cell_credit temp_credit;
    if (credit_queue.pop_if_not_empty(temp_credit))
    {
        temp_credit.dump_header("rx:", log.prefix());
        CreditInfo info;
        info.set_flow_id(temp_credit.flow_id());
        info.set_dest_tm_id(temp_credit.dest_id());
        info.set_src_tm_id(temp_credit.source_id());
        info.set_credit(256);
        credit_info_out.write(info);
        valid_credit_info_out.write(true);
        stat.increase_counter("credit_grant_rx", temp_credit.dest_id(), 1);
    }
    else
    {
        valid_credit_info_out.write(false);
    }
}

void rx::update_counter() { stat.update_counter("rx_queue_size", h.size()); }

bool rx::check_request_sequence(int src_id, int flow_id, int seq)
{
    if (conf.retrieve_config("rx_validate_reqseq") == 0)
    {
        return true;
    }
    if (last_reqseq.count(src_id) <= 0 || last_reqseq[src_id].count(flow_id) <= 0)
    {
        last_reqseq[src_id][flow_id] = seq;
        return true;
    }

    // if (seq > last_reqseq[src_id][flow_id] && seq <= (last_reqseq[src_id][flow_id] + ((1 << CELL_FLOWSTS_REQSEQ_SIZE)
    // - 1) / 2) % (1 << CELL_FLOWSTS_REQSEQ_SIZE))
    if (check_cycle_between((1 << CELL_FLOWSTS_REQSEQ_SIZE), last_reqseq[src_id][flow_id],
                            (last_reqseq[src_id][flow_id] + ((1 << CELL_FLOWSTS_REQSEQ_SIZE) - 1) / 2), seq))
    {
        last_reqseq[src_id][flow_id] = seq;
        return true;
    }
    log.prefix() << "rx:received old flow status " << seq << " from source " << src_id << std::endl;
    return false;
}

bool rx::check_cycle_between(int cycle_len, int start, int end, int x)
{
    start %= cycle_len;
    end %= cycle_len;
    x %= cycle_len;
    if (start <= end)
    {
        if (start <= x && x <= end)
            return true;
    }
    else
    {
        if ((start <= x && x < cycle_len) || (0 <= x && x <= end))
            return true;
    }
}
