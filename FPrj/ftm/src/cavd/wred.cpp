#include "wred.h"

void wred_pol::reset_thrs(unsigned val)
{
    for (int i = 0; i < VOQ_NUM; i++)
        q_thrs[i] = val;
}

wred_pol::wred_pol(ModuleLog & l) : log(l)
{
    for (int i = 0; i < VOQ_NUM; i++)
        q_size[i] = 0;
    for (int i = 0; i < VOQ_NUM; i++)
        q_thrs[i] = 0x3ff;
}

void wred_pol::incr(unsigned q_num)
{
    if (q_num > VOQ_NUM)
    {
        log.prefix() << "q size out range ! " << std::endl;
        return;
    }

    q_size[q_num]++;
}

void wred_pol::decr(unsigned q_num)
{
    if (q_num > VOQ_NUM)
    {
        log.prefix() << "q size out range ! " << std::endl;
        return;
    }

    --q_size[q_num];
}

void wred_pol::reset_size(void) { memset(&q_size, 0x0, VOQ_NUM * 4); }

int wred_pol::get_size(unsigned q_num)
{
    if (q_num > VOQ_NUM)
    {
        log.prefix() << "q size out range ! " << std::endl;
        return 0;
    }

    return q_size[q_num];
}

int wred_pol::get_thrs(unsigned q_num)
{
    if (q_num > VOQ_NUM)
    {
        log.prefix() << "q size out range ! " << std::endl;
        return 0;
    }

    return q_thrs[q_num];
}

void wred_pol::set_thrs(unsigned q_num, unsigned q_thrs_value)
{
    if (q_num > VOQ_NUM)
    {
        log.prefix() << "q size out range ! " << std::endl;
        return;
    }

    q_thrs[q_num] = q_thrs_value;
}

void wred::policy()
{
    rd_rqst.write(true);
    while (true)
    {
        pd_valid_out.write(false);

        if (dq_report_valid.read() == true)
        {
            log.prefix() << "q out !" << std::endl;
            wred_q.decr(dq_report.read().get_flow_id());
        }

        if (pd_fc.read() == false)
        {
            if (validPd.read() == true)
            {
                Pd_wred = Pd_in.read();

                log.prefix() << "clk is :" << sc_time_stamp() << "::" << wred_q.get_size(Pd_wred.get_flowID())
                             << "::" << wred_q.get_thrs(Pd_wred.get_flowID()) << std::endl;

                if (wred_q.get_size(Pd_wred.get_flowID()) < wred_q.get_thrs(Pd_wred.get_flowID()))
                {
                    log.prefix() << "q in !" << std::endl;
                    wred_q.incr(Pd_wred.get_flowID());
                    Pd_wred.set_result(false);
                }
                else
                {
                    log.prefix() << "drop !" << std::endl;
                    Pd_wred.set_result(true);
                }

                Pd_to_qm.write(Pd_wred);
                pd_valid_out.write(true);
                rd_rqst.write(true);
            }

        }
        else
        {
            rd_rqst.write(false);
        }

        wait();
    }
}