/*
 * @Description: Socket handler with priority queue
 * @Author: f21538
 * @Date: 2020-11-30 16:15:30
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 17:58:24
 */
#ifndef _QUEUE_SOCKET_HANDLER_H_
#define _QUEUE_SOCKET_HANDLER_H_
#include <SocketHandler.h>
#include <queue>

template <typename T, typename Container=std::queue<T> > class QueueSocketHandler : public SocketHandler
{
public:
    QueueSocketHandler() : SocketHandler(), q() {}

    void push(T &c) { q.push(c); }

    bool pop_if_not_empty(T &c)
    {
        if (q.empty())
        {
            return false;
        }

        c = q.top();
        q.pop();
        return true;
    }

    int size() { return q.size(); }

protected:
    //Container<T, std::vector<T>, std::greater<T> /**/> q;
    Container q;
};


template <typename T> class QueueSocketHandler<T, std::queue<T> > : public SocketHandler
{
public:
    QueueSocketHandler() : SocketHandler(), q() {}

    void push(T &c) { q.push(c); }

    bool pop_if_not_empty(T &c)
    {
        if (q.empty())
        {
            return false;
        }

        c = q.front();
        q.pop();
        return true;
    }

    int size() { return q.size(); }

protected:
    std::queue<T> q;
};
#endif