/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-14 15:07:21
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-18 11:23:03
 */
#ifndef _VOQ_H_
#define _VOQ_H_
#include "Flow.h"
#include <map>
class VOQ
{
public:
    VOQ() : credit_num(0), enabled(false), parent(nullptr) {}

    bool is_enabled() { return enabled; }
    void set_enabled(bool t) { enabled = t; }
    void schedule() { credit_num++; }

    inline int get_credit_num() { return credit_num; }
    inline void set_credit_num(int t) { credit_num = t; }
    inline Flow * get_parent() { return parent; }
    inline void set_parent(Flow * t) { parent = t; }

private:
    int credit_num;
    bool enabled;
    Flow * parent;
};

class VOQPool
{
public:
    static std::map<int, VOQ> VOQs;
};

#endif
