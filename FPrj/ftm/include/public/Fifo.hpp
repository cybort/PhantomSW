/*
 * @Author: your name
 * @Date: 2020-12-02 09:55:07
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-01-06 15:30:56
 * @Description: file content
 */
#ifndef _FIFO_H_
#define _FIFO_H_
#include "Exception.h"
#include <queue>
template <class T> class Fifo
{
public:
    Fifo();
    Fifo(unsigned max_size);
    void push(T const &element);
    T pop();
    bool is_full();
    bool is_empty() { return q.empty(); };
    int get_size() { return q.size(); };
    int get_max_size() { return this->max_size; };

private:
    std::queue<T> q;
    unsigned max_size;
};

template <class T> Fifo<T>::Fifo() { this->max_size = 32; }

template <class T> Fifo<T>::Fifo(unsigned max_size)
{
    if (max_size >= 512)
    {
        throw Exception("max_size must be less than 512");
    }
    if (max_size == 0)
    {
        throw Exception("max_size must be lager than 0");
    }
}

template <class T> void Fifo<T>::push(T const &element)
{
    if (q.size() < max_size)
    {
        q.push(element);
    }
}
#include "iostream"
template <class T> T Fifo<T>::pop()
{
    T ret = q.front();
    q.pop();

    return ret;
}

template <class T> bool Fifo<T>::is_full()
{
    if (q.size() == max_size)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif