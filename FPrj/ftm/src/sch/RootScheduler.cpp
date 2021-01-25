/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-19 16:33:32
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 14:56:39
 */
#include "RootScheduler.h"
#include "Exception.h"
#include "SE.h"

#define BIT_PER_BYTE 8
void RootScheduler::schedule()
{
    try
    {
        int current_bandiwidth = 0;
        sc_bv<LINK_NUM> valid = link_valid.read();
        for (int i = 0; i < LINK_NUM; i++) /*generate max 36 credit per clock*/
        {
            if (valid[i] == true)
            {
                current_bandiwidth += config.retrieve_config("serdes_rate", i);
            }
        }
        double current_credit =
            (double)current_bandiwidth /
            (ConfigDB::GetInstance().retrieve_config(flow_status_resolver_name.c_str(), "credit_weight") *
             BIT_PER_BYTE) /
            config.retrieve_config("system_frequency");
        // ConfigDB::GetInstance().retrieve_config("RootScheduler", "system_frequency");
        log.prefix() << "current_credit " << current_credit << std::endl;
        credit_remain += current_credit;

        log.prefix() << "credit_remain " << credit_remain << std::endl;
        while (credit_remain > 1)
        {
            if (SEPool::SEs[0].schedule())
            {
                credit_remain -= 1;
            }
            else
            {
                break;
            }
        }
    }
    catch (Exception & e)
    {
        std::cout << e.ToString() << std::endl << e.Stack() << std::endl;
    }
}
