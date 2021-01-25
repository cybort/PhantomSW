/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-18 10:29:45
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 10:07:20
 */
#ifndef _FLOW_STATUS_RESOLVER_H_
#define _FLOW_STATUS_RESOLVER_H_

#include "ConfigDB.h"
#include "CreditInfo.h"
#include "Flow.h"
#include "FlowStatusMessage.h"
#include "ModuleLog.h"
#include "SE.h"
#include "VOQ.h"
#include "systemc.h"
#include <vector>
#define SRC_MAX 2

#define L0_SE_NUM 96
#define L1_SE_NUM 384
#define L2_SE_NUM (3 * 1024)
#define L3_SE_NUM (24 * 1024)
#define L4_VOQ_NUM (2 * 96 * 1024)

#define L0_SE_BEGIN 1
#define L0_SE_END (L0_SE_BEGIN + L0_SE_NUM)
#define L1_SE_BEGIN (L0_SE_END)
#define L1_SE_END (L1_SE_BEGIN + L1_SE_NUM)
#define L2_SE_BEGIN (L1_SE_END)
#define L2_SE_END (L2_SE_BEGIN + L2_SE_NUM)
#define L3_SE_BEGIN (L2_SE_END)
#define L3_SE_END (L3_SE_BEGIN + L3_SE_NUM)
#define L4_VOQ_BEGIN 1
#define L4_VOQ_END (L4_VOQ_BEGIN + L4_VOQ_NUM)
SC_MODULE(FlowStatusResolver)
{
    sc_in<bool> clk;
    sc_in<FlowStatusMessage> flow_status_message_in;
    sc_in<bool> flow_status_message_in_valid;
    sc_out<CreditInfo> credit_info_out;
    sc_out<bool> credit_info_out_valid;

    ModuleLog log;
    ConfigAccesssor config;
    std::vector<int> monitor_voqs;
    std::vector<int> wait_time;

    void request();
    void monitor();
    void clean();
    int encode_voq_table_addr(int flow_id, int src_id);

    int timeout_th;

    SC_CTOR(FlowStatusResolver) : log(name()), config(name()), timeout_th(500)
    {
        SC_METHOD(request);
        sensitive << clk.pos();
        SC_METHOD(monitor);
        sensitive << clk.pos();

        config.register_config("credit_weight");
        config.update_config("credit_weight", 256);

        config.register_config("voq_table", ConfigDB::Repeated);
        config.register_config("flowid_table", ConfigDB::Repeated);
        config.register_config("srcid_table", ConfigDB::Repeated);

        for (int flowid = 0; flowid < 96 * 1024; flowid++)
        {
            for (int srcid = 0; srcid < SRC_MAX; srcid++)
            {
                int addr = encode_voq_table_addr(flowid, srcid);
                int voq = addr;
                config.update_config("voq_table", addr, voq);
                config.update_config("flowid_table", voq, flowid);
                config.update_config("srcid_table", voq, srcid);
            }
        }

        /*for (int l0 = L0_SE_BEGIN; l0 < L0_SE_END; l0++)
        {
            SEPool::SEs[0].bind(l0, l0, 0);
            for (int l1 = L1_SE_BEGIN; l1 < L1_SE_END; l1++)
            {
                SEPool::SEs[l0].bind(l1, l1, 0);
                for (int l2 = L2_SE_BEGIN; l2 < L2_SE_END; l2++)
                {
                    SEPool::SEs[l1].bind(l2, l2, 0);
                    for (int l3 = L3_SE_BEGIN; l3 < L3_SE_END; l3++)
                    {
                        SEPool::SEs[l2].bind(l3, l3, 0);
                        for (int l4 = L4_VOQ_BEGIN; l4 < L4_VOQ_END; l4++)
                        {
                            SEPool::SEs[l3].bind_voq(l4 + L3_SE_END, l4, 0);
                        }
                    }
                }
            }
        }*/
        SEPool::SEs[0].bind(1, 1, 0);
        for (int i = 0; i < 16; i++)
        {
            SEPool::SEs[1].bind_voq(i + 2, i, 0);
        }
    }
};
#endif
