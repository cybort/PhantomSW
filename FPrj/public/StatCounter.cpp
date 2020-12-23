/*
 * @Description:
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-18 11:05:32
 */
#include "StatCounter.h"

void StatCounterBase::register_counter(const std::string & module_name, const std::string & counter_name,
                                       CounterType type)
{
    std::lock_guard<std::mutex> guard(lock);
    if (constraint_counter_exists(module_name, counter_name)) /*counter exists*/
    {
        if (Repeated == type && Mono == counter_type_db[module_name][counter_name]) /*Mono switch to Repeated*/
        {
            counter_repeated_db[module_name][counter_name][0] = counter_mono_db[module_name][counter_name];
            counter_mono_db[module_name].erase(counter_name);
        }
        else if (Mono == type &&
                 Repeated ==
                     counter_type_db[module_name][counter_name]) /*Repeated switch to Mono, only keep first value*/
        {
            counter_mono_db[module_name][counter_name] = counter_repeated_db[module_name][counter_name][0];
            counter_repeated_db[module_name].erase(counter_name);
        }
    }
    else
    {
        if (Mono == type)
        {
            counter_mono_db[module_name].insert(std::make_pair(counter_name, 0));
        }
        else if (Repeated == type)
        {
            counter_repeated_db[module_name].insert(std::make_pair(counter_name, std::map<int, int>()));
        }
    }
    counter_type_db[module_name][counter_name] = type;
}

StatCounterBase::CounterType StatCounterBase::retrieve_counter_type(const std::string & module_name,
                                                                    const std::string & counter_name)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_counter_exists(module_name, counter_name))
    {
        std::cout << "Counter " << counter_name << " need to register first!" << std::endl;
        return StatCounterBase::Invalid;
    }

    return counter_type_db[module_name][counter_name];
}

void StatCounterBase::update_counter(const std::string & module_name, const std::string & counter_name, int value)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_counter_exists(module_name, counter_name))
    {
        std::cout << "Counter " << counter_name << " need to register first!" << std::endl;
        return;
    }

    if (constraint_counter_is_repeated(module_name, counter_name))
    {
        std::cout << "Repeated counter " << counter_name << " need address to update!" << std::endl;
        return;
    }

    counter_mono_db[module_name][counter_name] = value;
}

void StatCounterBase::update_counter(const std::string & module_name, const std::string & counter_name, int addr,
                                     int value)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_counter_exists(module_name, counter_name))
    {
        std::cout << "Counter " << counter_name << " need to register first!" << std::endl;
        return;
    }

    if (constraint_counter_is_mono(module_name, counter_name))
    {
        std::cout << "Mono counter " << counter_name << " don't need address!" << std::endl;
        return;
    }

    counter_repeated_db[module_name][counter_name][addr] = value;
}

void StatCounterBase::increase_counter(const std::string & module_name, const std::string & counter_name, int value)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_counter_exists(module_name, counter_name))
    {
        std::cout << "Counter " << counter_name << " need to register first!" << std::endl;
        return;
    }

    if (constraint_counter_is_repeated(module_name, counter_name))
    {
        std::cout << "Repeated counter " << counter_name << " need address to update!" << std::endl;
        return;
    }

    counter_mono_db[module_name][counter_name] = counter_mono_db[module_name][counter_name] + value;
}

void StatCounterBase::increase_counter(const std::string & module_name, const std::string & counter_name, int addr,
                                       int value)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_counter_exists(module_name, counter_name))
    {
        std::cout << "Counter " << counter_name << " need to register first!" << std::endl;
        return;
    }

    if (constraint_counter_is_mono(module_name, counter_name))
    {
        std::cout << "Mono counter " << counter_name << " don't need address!" << std::endl;
        return;
    }

    counter_repeated_db[module_name][counter_name][addr] = counter_repeated_db[module_name][counter_name][addr] + value;
}

void StatCounterBase::reset_counter(const std::string & module_name, const std::string & counter_name)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_counter_exists(module_name, counter_name))
    {
        std::cout << "Counter " << counter_name << " need to register first!" << std::endl;
        return;
    }

    if (constraint_counter_is_mono(module_name, counter_name))
    {
        counter_mono_db[module_name][counter_name] = 0;
    }
    else if (constraint_counter_is_repeated(module_name, counter_name))
    {
        counter_repeated_db[module_name][counter_name] = std::map<int, int>();
    }
}

void StatCounterBase::reset_counter(const std::string & module_name, const std::string & counter_name, int addr)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_counter_exists(module_name, counter_name))
    {
        std::cout << "Counter " << counter_name << " need to register first!" << std::endl;
        return;
    }

    if (constraint_counter_is_mono(module_name, counter_name))
    {
        std::cout << "Mono counter " << counter_name << " don't need address!" << std::endl;
        return;
    }

    counter_repeated_db[module_name][counter_name][addr] = 0;
}

int StatCounterBase::retrieve_counter(const std::string & module_name, const std::string & counter_name)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_counter_exists(module_name, counter_name))
    {
        std::cout << "Counter " << counter_name << " need to register first!" << std::endl;
        return 0;
    }

    if (constraint_counter_is_repeated(module_name, counter_name))
    {
        std::cout << "Repeated counter " << counter_name << " need address to retrieve!" << std::endl;
        return 0;
    }

    return counter_mono_db[module_name][counter_name];
}

int StatCounterBase::retrieve_counter(const std::string & module_name, const std::string & counter_name, int addr)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_counter_exists(module_name, counter_name))
    {
        std::cout << "Counter " << counter_name << " need to register first!" << std::endl;
        return 0;
    }

    if (constraint_counter_is_mono(module_name, counter_name))
    {
        std::cout << "Mono counter " << counter_name << " don't need address!" << std::endl;
        return 0;
    }

    return counter_repeated_db[module_name][counter_name][addr];
}

int StatCounterBase::retrieve_counter_size(const std::string & module_name, const std::string & counter_name)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_counter_exists(module_name, counter_name))
    {
        std::cout << "Counter " << counter_name << " need to register first!" << std::endl;
        return 0;
    }

    if (constraint_counter_is_mono(module_name, counter_name))
    {
        std::cout << "Mono counter " << counter_name << " don't have size!" << std::endl;
        return 0;
    }

    return counter_repeated_db[module_name][counter_name].size();
}

std::vector<std::string> & StatCounterBase::retrieve_module_list(std::vector<std::string> & list)
{
    std::lock_guard<std::mutex> guard(lock);
    for (auto iter = counter_type_db.begin(); iter != counter_type_db.end(); iter++)
    {
        list.push_back(iter->first);
    }
    return list;
}

std::vector<std::string> & StatCounterBase::retrieve_counter_list(const std::string & module_name,
                                                                  std::vector<std::string> & list)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_module_exists(module_name))
    {
        std::cout << "Module " << module_name << " don't exists!" << std::endl;
        return list;
    }

    for (auto iter = counter_type_db[module_name].begin(); iter != counter_type_db[module_name].end(); iter++)
    {
        list.push_back(iter->first);
    }
    return list;
}

bool StatCounterBase::constraint_module_exists(const std::string & module_name)
{
    return counter_type_db.count(module_name) > 0;
}
bool StatCounterBase::constraint_counter_exists(const std::string & module_name, const std::string & counter_name)
{
    return counter_type_db[module_name].count(counter_name) > 0;
}
bool StatCounterBase::constraint_counter_is_mono(const std::string & module_name, const std::string & counter_name)
{
    return Mono == counter_type_db[module_name][counter_name];
}
bool StatCounterBase::constraint_counter_is_repeated(const std::string & module_name, const std::string & counter_name)
{
    return Repeated == counter_type_db[module_name][counter_name];
}
