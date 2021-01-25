/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-19 09:25:09
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 10:12:32
 */
#include "SE.h"
#include "Flow.h"

SE::initializor init;
ModuleLog SE::log("SE");
std::map<int, SE> SEPool::SEs;

void SE::bind(int flowid, int next_se, int sp)
{
    FlowPool::flows[flowid].set_parent(this);
    FlowPool::flows[flowid].set_enabled(true);
    FlowPool::flows[flowid].bind_se(next_se);
    binded_flow[sp].insert(flowid);
}
void SE::bind_voq(int flowid, int next_voq, int sp)
{
    FlowPool::flows[flowid].set_parent(this);
    FlowPool::flows[flowid].set_enabled(true);
    FlowPool::flows[flowid].bind_voq(next_voq);
    binded_flow[sp].insert(flowid);
}
void SE::unbind_recursive()
{
    for (int sp = 0; sp < 8; sp++)
    {
        for (int id : binded_flow[sp])
        {
            FlowPool::flows[id].unbind_recursive();
            FlowPool::flows[id].set_parent(nullptr);
        }
        binded_flow[sp].clear();
    }
}
void SE::unbind(int flowid, int sp)
{
    if (binded_flow[sp].count(flowid) > 0)
    {
        FlowPool::flows[flowid].set_parent(nullptr);
        binded_flow[sp].erase(flowid);
    }
}

bool SE::wfq_schedule()
{
    int sp = 0; // 调度一次后, 下次从sp = 0开始

    for (; sp < 8; sp++)
    {
        int loop_num = binded_flow[sp].size();
        if (loop_num == 0)
        {
            log.prefix() << "sp " << sp << " is empty" << std::endl;
            continue;
        }

        std::vector<std::pair<int, int>> sp_weight = get_sp_wfq_weight(sp);

        auto iter = binded_flow[sp].find(last_choice[sp]);
        if (last_times[sp] == 0) // 剩余调度的次数, 类比权重, 当前flow没有调度次数
        {
            iter++;

            if (iter == binded_flow[sp].end())
            {
                iter = binded_flow[sp].begin();
            }
        }

        while (loop_num > 0 && !FlowPool::flows[*iter].schedule())
        {
            iter++;
            if (iter == binded_flow[sp].end())
            {
                iter = binded_flow[sp].begin();
            }

            loop_num--;
        }

        if (loop_num == 0) // 当前优先级不能调度, 找下一个优先级
        {
            continue;
        }
        else
        {
            // 给flow分配权重值
            if (last_choice[sp] !=
                *iter) // 如果上一次选择与当前的选择不相等, 说明上一次的选择的调度次数用完, 使用下一个flow, 并分配权重
            {
                int i = times[sp] % (sp_weight.size());
                last_times[sp] = sp_weight[i].second;
                times[sp]++; // 记录分配次数
            }

            // 轮询调度, 当前flow调度完成, 调度下一个, 从sp = 0开始
            last_choice[sp] = *iter;
            last_times[sp]--;

            return true;
        }
    }

    return false;
}

bool SE::fq_schedule()
{
    int sp = 0; // 调度一次后, 下次从sp = 0开始

    for (; sp < 8; sp++)
    {
        int loop_num = binded_flow[sp].size();

        if (loop_num == 0)
        {
            log.prefix() << "sp " << sp << " is empty" << std::endl;
            continue;
        }

        auto iter = binded_flow[sp].find(last_choice[sp]);
        iter++;

        if (iter == binded_flow[sp].end())
        {
            iter = binded_flow[sp].begin();
            log.prefix() << "sp " << sp << " reach end" << std::endl;
        }

        while (loop_num > 0 && !FlowPool::flows[*iter].schedule())
        {
            iter++;
            if (iter == binded_flow[sp].end())
            {
                iter = binded_flow[sp].begin();
                log.prefix() << "sp " << sp << " search to end" << std::endl;
            }

            loop_num--;
        }

        if (loop_num == 0) // 当前优先级不能调度, 找下一个优先级
        {
            log.prefix() << "sp " << sp << " all cannot schedule" << std::endl;
            continue;
        }
        else
        {
            // 轮询调度, 当前flow调度完成, 调度下一个, 从sp = 0开始
            log.prefix() << "flow " << *iter << " in sp " << sp << " scheduled " << std::endl;
            last_choice[sp] = *iter;
            return true;
        }
    }

    return false;
}

bool SE::schedule()
{
    // if (!is_initialized)
    // {
    //    initialize();
    //}

    bool can_sch;
    // ConfigAccesssor seConfig("SE");
    // seConfig.register_config("sch", ConfigDB::Mono);
    // seConfig.update_config("sch", 0); // 0表示fq, 1表示wfq
    int choice = config.retrieve_config("sch");

    switch (choice)
    {
    case 0:
        can_sch = fq_schedule();
        break;
    case 1:
        can_sch = wfq_schedule();
        break;
    default:
        std::cout << "There is no choice, please check the choice : fq or wfq!" << std::endl;
        break;
    }

    return can_sch;
}
