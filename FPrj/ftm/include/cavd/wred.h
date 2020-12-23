#ifndef _WRED_H_
#define _WRED_H_

#include "DeQueueReport.h"
#include "ModuleLog.h"
#include "pd.h"
#include "systemc.h"
#include <iostream>

#define MAX_Q_NUM (96 * 1024)

class wred_pol
{
private:
    unsigned int q_size[MAX_Q_NUM];
    unsigned int q_thrs[MAX_Q_NUM];
    ModuleLog & log;

public:
    wred_pol(ModuleLog & l);

    void incr(unsigned q_num);

    void decr(unsigned q_num);

    int get_size(unsigned q_num);

    void reset_size(void);

    int get_thrs(unsigned q_num);

    void set_thrs(unsigned q_num, unsigned q_thrs_value);

    void reset_thrs(unsigned val);
};

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

    wred_pol wred_q;
    void policy();

    SC_CTOR(wred) : log(name()), wred_q(log)
    {
        SC_THREAD(policy);
        sensitive << clk.pos();
    }
};

#endif