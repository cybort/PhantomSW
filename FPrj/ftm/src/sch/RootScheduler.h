/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-14 15:01:44
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 14:55:53
 */
#ifndef _CREDIT_GENERATER_H_
#define _CREDIT_GENERATER_H_

#include "ConfigDB.h"
#include "ModuleLog.h"
#include "systemc.h"
#define LINK_MAX 144
#define LINK_NUM LINK_MAX
#define SERDES_RATE 56 // Gbps
SC_MODULE(RootScheduler)
{
    sc_in<bool> clk;
    sc_in<sc_bv<LINK_NUM>> link_valid;
    int root_se;

    ModuleLog log;
    ConfigAccesssor config;
    double credit_remain;

    void schedule();
    std::string flow_status_resolver_name;
    SC_CTOR(RootScheduler) : root_se(0), config(name()), credit_remain(0), log(name())
    {
        SC_METHOD(schedule);
        sensitive << clk.pos();
        config.register_config("serdes_rate", ConfigDB::Repeated); // Mbps
        config.register_config("link_num");
        config.register_config("system_frequency");
        std::cout << "module " << name() << " register " << config.retrieve_config("system_frequency") << std::endl;

        for (int i = 0; i < LINK_NUM; i++)
        {
            config.update_config("serdes_rate", i, 56 * 1024);
        }

        config.update_config("link_num", 36);
        config.update_config("system_frequency", 1200);
    }
};
#endif
