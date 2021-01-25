/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-18 10:52:56
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 11:45:10
 */
#include "FlowStatusResolver.h"
#include "VOQ.h"
#include <algorithm>

void FlowStatusResolver::request()
{
    FlowStatusMessage current_flow_status;
    int voq_table_addr, voqid;
    if (flow_status_message_in_valid.read() == true)
    {
        current_flow_status = flow_status_message_in.read();
        voq_table_addr = encode_voq_table_addr(current_flow_status.get_flow_id(), current_flow_status.get_src_tm_id());
        voqid = config.retrieve_config("voq_table", voq_table_addr);
        if (current_flow_status.get_status() == CreditRequestStatus::STATUS_OFF)
        {
            VOQPool::VOQs[voqid].set_enabled(false);
            VOQPool::VOQs[voqid].set_credit_num(0);
            log.prefix() << "source id " << current_flow_status.get_src_tm_id() << " flow "
                         << current_flow_status.get_flow_id() << " voq " << voqid << " status set off" << std::endl;
            monitor_voqs.erase(
                std::remove_if(monitor_voqs.begin(), monitor_voqs.end(), [&](int t) { return t == voqid; }),
                monitor_voqs.end());
        }
        else
        {
            VOQPool::VOQs[voqid].set_enabled(true);
            log.prefix() << "source id " << current_flow_status.get_src_tm_id() << " flow "
                         << current_flow_status.get_flow_id() << " voq " << voqid << " status set on" << std::endl;

            auto pos = std::find(monitor_voqs.begin(), monitor_voqs.end(), voqid);
            if (pos == std::end(monitor_voqs))
            {
                monitor_voqs.push_back(voqid);
            }
        }
    }
}

void FlowStatusResolver::monitor()
{
    credit_info_out_valid.write(false);
    for (auto iter_voq = monitor_voqs.begin(); iter_voq != monitor_voqs.end();)
    {
        int voqid = *iter_voq;
        if (VOQPool::VOQs[voqid].get_credit_num() > 0 && VOQPool::VOQs[voqid].is_enabled())
        {
            CreditInfo credit;
            int credit_destid = config.retrieve_config("srcid_table", voqid);
            int credit_flowid = config.retrieve_config("flowid_table", voqid);
            credit.set_credit(VOQPool::VOQs[voqid].get_credit_num() * config.retrieve_config("credit_weight"));
            VOQPool::VOQs[voqid].set_credit_num(0);
            credit.set_dest_tm_id(credit_destid);
            credit.set_flow_id(credit_flowid);
            credit_info_out.write(credit);
            credit_info_out_valid.write(true);
            log.prefix() << "voq " << voqid << " grant credit " << credit.get_credit() << " send to dest id "
                         << credit_destid << " flow " << credit_flowid << std::endl;
            // iter_voq = monitor_voqs.erase(iter_voq);
            // iter_time = wait_time.erase(iter_time);
            iter_voq++;
            break;
        }
        else
        {
            iter_voq++;
        }
    }
}

void FlowStatusResolver::clean()
{
#if 0 
    for (auto iter_voq = monitor_voqs.begin(), iter_time = wait_time.begin();
         iter_voq != monitor_voqs.end(), iter_time != wait_time.end();)
    {
        (*iter_time)++;
        int voqid = *iter_voq;
      
        if (wait_time[voqid] > timeout_th)
        {
            Flow * parent_flow = VOQPool::VOQs[voqid].get_parent();
            SE * parent_SE = nullptr;

            while (parent_flow != nullptr && parent_flow->get_parent() != nullptr)
            {
                parent_SE = parent_flow->get_parent();
                parent_flow = parent_SE->get_parent();
            }
            if (parent_SE != &SEPool::SEs[0]) /*unmapped */
            {
                log.prefix() << "unmapped voq" << voqid << " timeout " << std::endl;
                iter_voq = monitor_voqs.erase(iter_voq);
                iter_time = wait_time.erase(iter_time);
                continue;
            }
        }

        iter_voq++;
        iter_time++;
    }
#endif
}

int FlowStatusResolver::encode_voq_table_addr(int flow_id, int src_id) { return src_id + flow_id * SRC_MAX; }
