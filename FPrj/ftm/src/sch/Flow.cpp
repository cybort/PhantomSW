/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-18 17:42:24
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 09:52:23
 */
#include "Flow.h"
#include "SE.h"
#include "VOQ.h"

ModuleLog Flow::log("Flow");
std::map<int, Flow> FlowPool::flows;

void Flow::bind_se(int next_se)
{
    if (next_id != 0)
    {
        unbind();
    }
    next_id = next_se;
    leaf_node = false;
    SEPool::SEs[next_id].set_parent(this);
}

void Flow::bind_voq(int next_voq)
{
    if (next_id != 0)
    {
        unbind();
    }
    next_id = next_voq;
    leaf_node = true;
    VOQPool::VOQs[next_id].set_parent(this);
}

void Flow::unbind_recursive()
{
    if (leaf_node)
    {
        VOQPool::VOQs[next_id].set_enabled(false);
        VOQPool::VOQs[next_id].set_parent(nullptr);
    }
    else
    {
        SEPool::SEs[next_id].unbind_recursive();
        SEPool::SEs[next_id].set_parent(nullptr);
    }
    enabled = false;
    next_id = 0;
}

void Flow::unbind()
{
    if (leaf_node)
    {
        VOQPool::VOQs[next_id].set_parent(nullptr);
    }
    else
    {
        SEPool::SEs[next_id].set_parent(nullptr);
    }
    enabled = false;
    next_id = 0;
}

bool Flow::schedule()
{
    if (can_schedule())
    {

        if (leaf_node)
        {
            log.prefix() << "try to schedult VOQ " << next_id << std::endl;
            if (VOQPool::VOQs[next_id].is_enabled())
            {
                VOQPool::VOQs[next_id].schedule();
                current_credit--;
                log.prefix() << "voq " << next_id << " scheduled" << std::endl;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            log.prefix() << "try to schedult SE " << next_id << std::endl;
            if (SEPool::SEs[next_id].schedule())
            {
                log.prefix() << "SE " << next_id << " scheduled" << std::endl;
                current_credit--;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
}
