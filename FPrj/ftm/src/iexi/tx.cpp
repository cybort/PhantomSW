#include "tx.h"

#include "ClientServerLong.h"
#include "Exception.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <thread>

void tx::sch()
{
    for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
    {
        if (valid[i].read() == true)
        {
            cell c = data[i].read();
            if (!c.is_empty())
            {
                qh.push(c);
                if (debug)
                {
                    c.dump_header("tx sch:", log.prefix());
                }
                last_clock = current_clock; /*last time received cell*/
            }
            current_t = c.timeslot();
        }
    }

    if (true == valid_credit_request.read())
    {
        if (debug)
        {
            cell_flowsts temp = credit_request.read();
            temp.dump_header("tx sch:", log.prefix());
        }
        cell c(credit_request.read());
        qh.push(c);
    }

    if (true == valid_credit_grant.read())
    {
        if (debug)
        {
            cell_credit temp = credit_grant.read();
            temp.dump_header("tx sch:", log.prefix());
        }
        cell c(credit_grant.read());
        qh.push(c);
    }

    // static int t = 0;
    // if (current_t < 50)
    //{
    /*//test_mode
      current_t++;
      cell c;
      c.packet_id(t);
      t+=2;
      c.cell_id(current_t);
      qh.push(c);
      */
    //}
}

void tx::shuffle()
{
    cell c;
    int i;
    if (shuffle_depth > 1)
    {
        while (qh.pop_if_not_empty(c))
        {
            shuffle_queue.push_back(c);
        }
        if (shuffle_queue.size() >= shuffle_depth ||
            (shuffle_queue.size() > 0 &&
             current_clock - last_clock >= shuffle_depth)) /*queue is full or reach wait time*/
        {

            std::random_shuffle(shuffle_queue.begin(), shuffle_queue.end());

            int len = shuffle_queue.size();

            for (i = 0; i < len / 2 + 1 && i < shuffle_queue.size(); i++)
            {
                shuffle_queue[i].dump_header("after shuffle", log.prefix());
                transfer_queue.push(shuffle_queue[i]);
                // shuffle_queue.erase(shuffle_queue.begin()+i);
            }

            // shuffle_queue.clear();
            shuffle_queue.erase(shuffle_queue.begin(), shuffle_queue.begin() + i);
            log.prefix() << "====================================" << endl;
        }

        if (INT_MAX > current_clock)
        {
            current_clock++;
        }
        else
        {
            current_clock = last_clock = 0;
        }
    }
    else
    {
        if (shuffle_queue.size() > 0)
        {
            for (i = 0; i < shuffle_queue.size(); i++)
            {
                transfer_queue.push(shuffle_queue[i]);
            }
            shuffle_queue.clear();
        }
        while (qh.pop_if_not_empty(c))
        {
            transfer_queue.push(c);
        }
    }
}
/*
void tx::connect()
{
    try {
          for (int i = 0; i < SEND_SOCKETS_NUM; i++)
          {
              while (!cc[i]->IsConnected())
              {
                  cc[i]->Open(SW_IP, SW_BASE_SERVER_PORT+i);
                  h.Add(cc[i]);
                  h.Select(1,1);
                  if (!cc[i]->IsConnected())
                  {
                      log.prefix()<<i<<" unconnected"<<std::endl;
                      delete cc[i];
                      cc[i] = new ClientSocketLong<cell>(h);
                      sleep(1);
                      keeper.inc(period);
                      if (keeper.need_sync())
                         keeper.sync();
                  }
                  else
                  {
                      std::cout<<"True"<<i<<std::endl;
                      break;
                  }
              }
          }
      }
      catch (Exception& e)
      {
          std::cout<<e.ToString()<<endl<<e.Stack()<<endl;
      }
}*/

void tx::socket()
{
    sc_time period(1, SC_MS);
    while (true)
    {
        // std::cout<<"press any key after switch start"<<endl;
        // getchar();

        try
        {
            for (int i = 0; i < SEND_SOCKETS_NUM; i++)
            {

                if (!cc[i]->IsConnected())
                {
                    cc[i]->Open(SW_IP, SW_BASE_SERVER_PORT + i);
                    h[i].Add(cc[i]);
                }

                h[i].Select(1, 0);
                /*if (!cc[i]->IsConnected())
                {
                    log.prefix() << i << " unconnected" << std::endl;
                    delete cc[i];
                    cc[i] = new ClientSocketLong<cell>(h[i]);
                    usleep(1000);
                    keeper.inc(sc_time(1, SC_MS));
                    if (keeper.need_sync())
                        keeper.sync();
                }
                else
                {
                    // std::cout << "True" << i << std::endl;
                    break;
                }*/
            }

            /*for (int i = 0; i < SEND_SOCKETS_NUM; i++)
            {
                h[i].Select(0, 1);
            }*/
            while (true)
            {
                for (int i = 0; i < SEND_SOCKETS_NUM; i++)
                {
                    if (h[i].GetCount())
                    {
                        h[i].Select(0, 1);
                        keeper.inc(period);
                        if (keeper.need_sync())
                            keeper.sync();
                    }
                    else
                    {
                        log.prefix() << "No. " << i << " socket disconnected" << std::endl;
                        delete cc[i];
                        cc[i] = new ClientSocketLong<cell>(h[i]);
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                        keeper.inc(period);
                        if (keeper.need_sync())
                            keeper.sync();
                        cc[i]->Open(SW_IP, SW_BASE_SERVER_PORT + i);
                        h[i].Add(cc[i]);
                        h[i].Select(1, 0);
                    }
                }
            }
        }
        catch (Exception & e)
        {
            std::cout << e.ToString() << endl << e.Stack() << endl;
        }
    }
}

void tx::send()
{
    sc_time period(1, SC_MS);
    SocketHandler h;
    int old_i = SEND_SOCKETS_NUM;
#if USE_RANDOM_LOAD_BALANCING
    for (int i = 0;; i = (rand()) % SEND_SOCKETS_NUM)
#else
    for (int i = 0;; i = (i + 1) % SEND_SOCKETS_NUM)
#endif
    {
        if (used[i] == true || i == old_i)
        {
            // std::cout<<"continue i "<<i<<" old i "<<old_i<<endl;
            // for (int j = 0; j < SEND_SOCKETS_NUM;j++) std::cout<<used[j]<<" ";
            // std::cout<<endl;
            // getchar();
            continue;
        }
        cell c;
        // std::cout<<"used_num "<<used_num<<" used i "<<used[i]<<endl;
        used_num++;
        used[i] = true;
        old_i = i;
        if (transfer_queue.pop_if_not_empty(c))
        {
            // std::cout<<"send packet id(timeslot): "<<c.packet_id()<<"    cell id(sequence): "<<c.cell_id()<<" port:
            // "<<SW_BASE_SERVER_PORT+i<<std::endl;
            if (debug)
            {
                log.prefix() << "sending to port: " << SW_BASE_SERVER_PORT + i << endl;
            }
            switch (c.type)
            {
            case CellType::Unicast:
                cc[i]->SendWithEncode(c.raw_data, sizeof(cell_unicast));
                break;
            case CellType::FlowSts:
                cc[i]->SendWithEncode(c.raw_data, sizeof(cell_flowsts));
                break;
            case CellType::Credit:
                cc[i]->SendWithEncode(c.raw_data, sizeof(cell_credit));
                break;
            }

            keeper.inc(period);
            if (keeper.need_sync())
                keeper.sync();
        }
        else
        {
            cell temp;
            temp.timeslot(current_t);
            temp.set_empty();
            temp.source_id(SRC_TM_ID);
            temp.refresh_crc();
            // std::cout<<"tx:send empty cell timeslot:"<< current_t << " port:" << SW_BASE_SERVER_PORT+i << " type: "<<
            // temp.type <<std::endl;
            cc[i]->SendWithEncode(temp.raw_data, sizeof(temp));
            keeper.inc(period);
            if (keeper.need_sync())
                keeper.sync();
        }
        /*clear flag*/
        if (used_num == SEND_SOCKETS_NUM)
        {
            for (int j = 0; j < SEND_SOCKETS_NUM; j++)
            {
                used[j] = false;
            }
            used_num = 0;
        }
    }
}

void tx::update_counter()
{
    stat.update_counter("pre_queue_size", qh.size());
    stat.update_counter("shuffle_queue_size", shuffle_queue.size());
    stat.update_counter("transfer_queue_size", transfer_queue.size());
}
