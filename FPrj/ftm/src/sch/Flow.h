/*
 * @Description:Flow
 * @Author: f21538
 * @Date: 2021-01-13 10:49:00
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 09:43:10
 */
#ifndef _FLOW_H_
#define _FLOW_H_
#include "ConfigDB.h"
#include "ModuleLog.h"
#include <map>
#include <set>

class SE;
class Flow
{
public:
    static ModuleLog log;
    Flow(int max = 3) : max_credit(max), current_credit(max), enabled(false), parent(nullptr) {}

    void bind_se(int next_se);
    void bind_voq(int next_voq);
    void unbind_recursive();
    void unbind();
    bool schedule();
    bool can_schedule() { return enabled && current_credit >= 0; }
    bool is_enabled() { return enabled; }
    void set_enabled(bool t) { enabled = t; }
    bool is_leaf_node() { return leaf_node; }
    void add_credit()
    {
        current_credit++;
        if (current_credit > max_credit)
        {
            current_credit = max_credit;
        }
    }

    inline void set_max_credit(int t) { max_credit = t; }
    inline int get_max_credit() { return max_credit; }
    inline void set_current_credit(int t) { current_credit = t; }
    inline int get_current_credit() { return current_credit; }
    inline int get_next_id() { return next_id; }
    inline void set_parent(SE * t) { parent = t; }
    inline SE * get_parent() { return parent; }

private:
    int max_credit;
    int current_credit;
    int next_id;
    bool enabled;
    bool leaf_node;
    SE * parent;
};

class FlowPool
{
public:
    static std::map<int, Flow> flows;
};

/*
int sc_main(int argc, char * argv[])
{
    for (int i = 1; i <= 10; i++)
    {
        SEPool::SEs[i].bind(i, i + 1);
        SEPool::SEs[i].bind(15 * i, 15 * i + 1);
    }
    SEPool::SEs[0].bind(0, 1);

    sc_clock clk("clk", sc_time(20, SC_MS), 0.5, sc_time(1, SC_MS));
    FlowCreditFiller fcf("FlowCreditFiller");
    fcf.clk(clk);

    CreditGenerater cg("CreditGenerater");
    cg.root_se = 0;
    cg.clk(clk);

    sc_start();

    return 0;
}*/
#endif
