/*
 * @Description: Transfer cells to switch
 * @Author: f21538
 * @Date: 2020-11-27 18:12:14
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-21 09:36:56
 */
#ifndef _TX_H_
#define _TX_H_

#include "ClientServerLong.h"
#include "CreditInfo.h"
#include "FlowStatusMessage.h"
#include "ModuleLog.h"
#include "QueueSocketHandler.h"
#include "StatCounter.h"
#include "cell.h"
#include "port.h"
#include "simple_queue.h"
#include "tlm_utils/tlm_quantumkeeper.h"
#include <SocketHandler.h>
#include <algorithm>
#include <cstdlib>
#include <vector>

SC_MODULE(tx)
{
    bool debug;
    sc_in<bool> clk;

    sc_in<bool> valid[TM_CELL_PER_CLOCK_LIMIT];
    sc_in<cell> data[TM_CELL_PER_CLOCK_LIMIT];

    sc_in<cell_flowsts> credit_request;
    sc_in<bool> valid_credit_request;

    sc_in<cell_credit> credit_grant;
    sc_in<bool> valid_credit_grant;

    tlm_utils::tlm_quantumkeeper keeper;
    QueueSocketHandler<cell> qh;
    std::vector<SocketHandler> h;
    std::vector<bool> used;
    std::vector<ClientSocketLong<cell> *> cc;

    int current_t;
    int used_num;
    int shuffle_depth;
    int current_clock;
    int last_clock;

    ModuleLog log;
    StatCounter stat;

    std::vector<cell> shuffle_queue;
    simple_queue<cell> transfer_queue;

    void sch();
    void shuffle();
    void socket();
    void send();
    void update_counter();

    SC_CTOR(tx)
        : debug(false), log(name()), stat(name()), shuffle_depth(0), cc(SEND_SOCKETS_NUM), used(SEND_SOCKETS_NUM),
          h(SEND_SOCKETS_NUM)
    {
        tlm_utils::tlm_quantumkeeper::set_global_quantum(sc_time(10, SC_MS));
        keeper.reset();
        SC_METHOD(sch);
        sensitive << clk.pos();
        SC_METHOD(shuffle);
        sensitive << clk.pos();
        SC_THREAD(socket);
        sensitive << clk.pos();
        SC_THREAD(send);
        sensitive << clk.pos();
        SC_METHOD(update_counter);
        sensitive << clk.pos();
        current_t = 0;
        used_num = 0;
        current_clock = 0;
        last_clock = 0;

        for (int i = 0; i < SEND_SOCKETS_NUM; i++)
        {
            cc[i] = new ClientSocketLong<cell>(h[i]);
            used[i] = false;
        }

        stat.register_counter("pre_queue_size");
        stat.register_counter("shuffle_queue_size");
        stat.register_counter("transfer_queue_size");
    }

    ~tx()
    {
        for (int i = 0; i < LISTEN_SOCKETS_NUM; i++)
        {
            if (cc[i] != NULL)
            {
                delete cc[i];
            }
            else
            {
                log.prefix() << "Socket number " << i << " missed!" << std::endl;
            }
        }
    }
};

#endif
