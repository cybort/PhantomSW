/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-14 14:38:56
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-22 18:09:15
 */
#ifndef _SE_H_
#define _SE_H_

#include "ConfigDB.h"
#include "ModuleLog.h"
#include <map>
#include <set>

class Flow;
class FlowPool;

class SE
{
public:
    static ModuleLog log;
    SE() : config("SE") {}
    void bind(int flowid, int next_se, int sp);
    void bind_voq(int flowid, int next_voq, int sp);
    void unbind_recursive();
    void unbind(int flowid, int sp);
    bool fq_schedule(); // 公平调度, 也就是1:1:1:1..., wfq调度的特殊情况
    std::set<int> & get_binded_flow() { return binded_flow[8]; }

    inline void set_parent(Flow * t) { parent = t; }
    inline Flow * get_parent() { return parent; }
    ConfigAccesssor config;

    std::vector<std::pair<int, int>> get_sp_wfq_weight(int sp)
    {

        // wfqConfig.register_config("weight", ConfigDB::Repeated);

        // for (int i = 0; i < 4; i++)
        // {
        //     wfqConfig.update_config("weight", i,
        //                             i + 1); // 使用map存储的, 遍历时, 按照key遍历, key是顺序的,
        //                             因此weight是按照顺序来的
        // }
        weight[sp].clear();
        config.retrieve_config_lines("weight", weight[sp]);

        return weight[sp];
    }

    bool wfq_schedule();
    bool schedule();
    class initializor
    {
    public:
        initializor()
        {
            ConfigDB::GetInstance().register_config("SE", "weight", ConfigDB::Repeated);
            ConfigDB::GetInstance().register_config("SE", "sch", ConfigDB::Mono);
            for (int i = 0; i < 4; i++)
            {
                ConfigDB::GetInstance().update_config("SE", "weight", i, i + 1);
            }
            ConfigDB::GetInstance().update_config("SE", "sch", 0);
        }
    };

private:
    std::set<int /*flowid*/> binded_flow[8];
    int last_choice[8];
    Flow * parent;

    // wfq调度
    std::vector<std::pair<int, int>> weight[8];
    int last_times[8]; // 一个flow调度的次数, 模拟权重
    int times[8];      // 一组flow使用的次数

    static initializor init;
    static bool is_initialized;
    void initialize()
    {
        is_initialized = true;
        ConfigDB::GetInstance().register_config("SE", "weight", ConfigDB::Repeated);
        ConfigDB::GetInstance().register_config("SE", "sch", ConfigDB::Mono);
        for (int i = 0; i < 4; i++)
        {
            ConfigDB::GetInstance().update_config("SE", "weight", i, i + 1);
        }
        ConfigDB::GetInstance().update_config("SE", "sch", 0);
    }
};
class SEPool
{
public:
    static std::map<int, SE> SEs;
};
#endif
