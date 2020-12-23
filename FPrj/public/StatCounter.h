/*
 * @Description: Counter database
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-18 11:03:49
 */
#ifndef _STAT_COUNTER_H_
#define _STAT_COUNTER_H_
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class StatCounterBase
{
public:
    enum CounterType
    {
        Mono,
        Repeated,
        Invalid
    };

    static StatCounterBase & GetInstance()
    {
        static StatCounterBase instance;
        return instance;
    }

    void register_counter(const std::string & module_name, const std::string & counter_name, CounterType type);
    CounterType retrieve_counter_type(const std::string & module_name, const std::string & counter_name);
    void update_counter(const std::string & module_name, const std::string & counter_name, int value); /*for mono*/
    void update_counter(const std::string & module_name, const std::string & counter_name, int addr,
                        int value); /*for repeated*/
    void increase_counter(const std::string & module_name, const std::string & counter_name, int value); /*for mono*/
    void increase_counter(const std::string & module_name, const std::string & counter_name, int addr,
                          int value);                                                      /*for repeated*/
    void reset_counter(const std::string & module_name, const std::string & counter_name); /*for mono & repeated*/
    void reset_counter(const std::string & module_name, const std::string & counter_name, int addr);   /*for repeated*/
    int retrieve_counter(const std::string & module_name, const std::string & counter_name);           /*for mono*/
    int retrieve_counter(const std::string & module_name, const std::string & counter_name, int addr); /*for repeated*/
    int retrieve_counter_size(const std::string & module_name, const std::string & counter_name);      /*for repeated*/

    std::vector<std::string> & retrieve_module_list(std::vector<std::string> & list);
    std::vector<std::string> & retrieve_counter_list(const std::string & module_name, std::vector<std::string> & list);

protected:
    std::mutex lock;
    bool constraint_module_exists(const std::string & module_name);
    bool constraint_counter_exists(const std::string & module_name, const std::string & counter_name);
    bool constraint_counter_is_mono(const std::string & module_name, const std::string & counter_name);
    bool constraint_counter_is_repeated(const std::string & module_name, const std::string & counter_name);

private:
    StatCounterBase() {}
    StatCounterBase(const StatCounterBase &) {}
    StatCounterBase & operator=(const StatCounterBase &) {}

    std::map<std::string /*module_name*/, std::map<std::string /*register_name*/, CounterType> > counter_type_db;
    std::map<std::string /*module_name*/, std::map<std::string /*register_name*/, int /*value*/> > counter_mono_db;
    std::map<std::string /*module_name*/,
             std::map<std::string /*register_name*/, std::map<int /*addr*/, int /*value*/> > >
        counter_repeated_db;
};

class StatCounter /*design for bind to sc_module*/
{
public:
    StatCounter(const std::string & module_name) : module(module_name) {}

    void register_counter(const std::string & counter_name, StatCounterBase::CounterType type = StatCounterBase::Mono)
    {
        StatCounterBase::GetInstance().register_counter(module, counter_name, type);
    }

    StatCounterBase::CounterType retrieve_counter_type(const std::string & counter_name)
    {
        return StatCounterBase::GetInstance().retrieve_counter_type(module, counter_name);
    }

    void update_counter(const std::string & counter_name, int value)
    {
        StatCounterBase::GetInstance().update_counter(module, counter_name, value);
    }

    void update_counter(const std::string & counter_name, int addr, int value)
    {
        StatCounterBase::GetInstance().update_counter(module, counter_name, addr, value);
    }

    void increase_counter(const std::string & counter_name, int value)
    {
        StatCounterBase::GetInstance().increase_counter(module, counter_name, value);
    }

    void increase_counter(const std::string & counter_name, int addr, int value)
    {
        StatCounterBase::GetInstance().increase_counter(module, counter_name, addr, value);
    }

    void reset_counter(const std::string & counter_name)
    {
        StatCounterBase::GetInstance().reset_counter(module, counter_name);
    }

    void reset_counter(const std::string & counter_name, int addr)
    {
        StatCounterBase::GetInstance().reset_counter(module, counter_name, addr);
    }

    int retrieve_counter(const std::string & counter_name)
    {
        return StatCounterBase::GetInstance().retrieve_counter(module, counter_name);
    }

    int retrieve_counter(const std::string & counter_name, int addr)
    {
        return StatCounterBase::GetInstance().retrieve_counter(module, counter_name, addr);
    }

    int retrieve_counter_size(const std::string & counter_name)
    {
        return StatCounterBase::GetInstance().retrieve_counter_size(module, counter_name);
    }

private:
    std::string module;
};

#endif
