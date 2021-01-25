/*
 * @Description: Transfer cells to switch
 * @Author: f21538
 * @Date: 2020-11-27 18:12:14
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 14:17:48
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
#define LINK_MAX 144
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

    sc_out<sc_bv<LINK_MAX>> link_valid_out;

    bool link_status[LINK_MAX];

    tlm_utils::tlm_quantumkeeper keeper;
    QueueSocketHandler<cell> qh;
    std::vector<SocketHandler> h;
    std::vector<bool> used;
    std::vector<ClientSocketLong<cell> *> cc;
    std::vector<std::string> link_ip;
    std::vector<int> link_port;

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
          h(SEND_SOCKETS_NUM), link_ip(SEND_SOCKETS_NUM), link_port(SEND_SOCKETS_NUM)
    {
        tlm_utils::tlm_quantumkeeper::set_global_quantum(sc_time(20, SC_MS));
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

        /*just for 2+2*/
        /*for (int i = 0; i < 18; i++)
        {
            link_ip[i] = SW0_IP;
        }
        for (int i = 18; i < 36; i++)
        {
            link_ip[i] = SW1_IP;
        }
        for (int i = 0; i < 18; i++)
        {
            link_port[i] = SW_BA_PORT + 18*SRC_TM_ID + i;
        }
        for (int i = 18; i < 36; i++)
        {
            link_port[i] = SW_BA_PORT + 18*SRC_TM_ID + (i-18);
        }*/

        for (int i = 0; i < SEND_SOCKETS_NUM / 2; i++)
        {
            link_ip[i] = SW0_IP;
        }
        for (int i = SEND_SOCKETS_NUM / 2; i < SEND_SOCKETS_NUM; i++)
        {
            link_ip[i] = SW1_IP;
        }
        for (int i = 0; i < SEND_SOCKETS_NUM / 2; i++)
        {
            link_port[i] = SW0_BA_PORT + 18 * SRC_TM_ID + i;
        }
        for (int i = SEND_SOCKETS_NUM / 2; i < SEND_SOCKETS_NUM; i++)
        {
            link_port[i] = SW1_BA_PORT + 18 * SRC_TM_ID + (i - SEND_SOCKETS_NUM / 2);
        }

        for (int i = 0; i < SEND_SOCKETS_NUM; i++)
        {
            cc[i] = new ClientSocketLong<cell>(h[i]);
            used[i] = false;
        }

        stat.register_counter("pre_queue_size");
        stat.register_counter("shuffle_queue_size");
        stat.register_counter("transfer_queue_size");
        stat.register_counter("flow_status_tx", StatCounterBase::Repeated);
        stat.register_counter("credit_grant_tx", StatCounterBase::Repeated);
    }

    ~tx()
    {
        for (int i = 0; i < SEND_SOCKETS_NUM; i++)
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
