/*
 * @Author: your name
 * @Date: 2021-01-06 14:44:16
 * @LastEditTime: 2021-01-25 11:37:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /w21064/F20210106/trunk/FPrj/ftm/include/cavd/wred.h
 */
#ifndef _WRED_H_
#define _WRED_H_

#include "DeQueueReport.h"
#include "ModuleLog.h"
#include "pd.h"
#include "systemc.h"
#include <iostream>

#define MAX_Q_NUM (96 * 1024)

#include "ConfigDB.h"
#include "StatCounter.h"

SC_MODULE(wred)
{
    sc_in<bool> clk;
    /*  vif <-> wred */
    sc_in<bool> validPd;
    sc_in<pd> Pd_in;
    sc_out<bool> rd_rqst;

    /* vif <-> pd queue manager */
    sc_out<bool> pd_valid_out;
    //   sc_in<sch_info>     sch;
    //   sc_in<bool>         sch_valid;
    sc_in<bool> pd_fc;
    sc_out<pd> Pd_to_qm;
    sc_in<bool> dq_report_valid;
    sc_in<DeQueueReport> dq_report;

    pd Pd_wred;
    ModuleLog log;

    unsigned int q_size[MAX_Q_NUM];
    unsigned int q_thrs[MAX_Q_NUM];
    ConfigAccesssor wredConfig;
    StatCounter wredCounter;

    void incr(unsigned q_num, int bytes);
    void decr(unsigned q_num, int bytes);
    int get_size(unsigned q_num);
    void reset_size(void);
    int get_thrs(unsigned q_num);
    void set_thrs(unsigned q_num, unsigned q_thrs_value);
    void reset_thrs(unsigned val);

    void policy();

    SC_CTOR(wred) : log(name()), wredConfig(name()), wredCounter(name())
    {
        wredConfig.register_config("thrs", ConfigDB::Repeated);
        wredCounter.register_counter("pass");
        wredCounter.register_counter("drop");
        for (int i = 0; i < VOQ_NUM; i++)
            q_size[i] = 0;
        for (int i = 0; i < VOQ_NUM; i++)
        {
            wredConfig.update_config("thrs", i, 1000000000);
            q_thrs[i] = wredConfig.retrieve_config("thrs", i); // 这个值从外部设置,从外部读取
            // log.prefix() << "wred q:" << i << "thrs:" << q_thrs[i] << std::endl;
        }

        SC_THREAD(policy);
        sensitive << clk.pos();
    }
};

#endif
