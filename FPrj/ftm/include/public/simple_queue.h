/*
 * @Description: No block simple queue
 * @Author: f21538
 * @Date: 2020-11-27 18:12:14
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 11:26:10
 */
#ifndef _SIMPLE_QUEUE_H_
#define _SIMPLE_QUEUE_H_
#include <queue>

template <typename T> class simple_queue : public std::queue<T>
{
    public:
    simple_queue() {}

    bool pop_if_not_empty(T &c)
    {
        if (this->empty())
        {
            return false;
        }

        c = this->front();
        this->pop();
        return true;
    }
};

template <typename T, typename Comparetor = std::less<T> > class simple_prio_queue : public std::priority_queue<T, typename std::priority_queue<T>::container_type, Comparetor>
{
    public:
    simple_prio_queue() {}

    bool pop_if_not_empty(T &c)
    {
        if (this->empty())
        {
            return false;
        }

        c = this->top();
        this->pop();
        return true;
    }
};
#endif