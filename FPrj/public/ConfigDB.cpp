/*
 * @Description:
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-04 13:41:33
 */
#include "ConfigDB.h"
#include <Exception.h>
#include <cassert>

void ConfigDB::register_config(const std::string & module_name, const std::string & config_name, ConfigType type)
{
    assert(type != ConfigDB::Invalid);
    std::lock_guard<std::mutex> guard(lock);
    if (constraint_config_exists(module_name, config_name)) /*counter exists*/
    {
        if (Repeated == type && Mono == config_type_db[module_name][config_name]) /*Mono switch to Repeated*/
        {
            config_repeated_db[module_name][config_name][0] = config_mono_db[module_name][config_name];
            config_mono_db[module_name].erase(config_name);
        }
        else if (Mono == type &&
                 Repeated ==
                     config_type_db[module_name][config_name]) /*Repeated switch to Mono, only keep first value*/
        {
            config_mono_db[module_name][config_name] = config_repeated_db[module_name][config_name][0];
            config_repeated_db[module_name].erase(config_name);
        }
    }
    else
    {
        if (Mono == type)
        {
            config_mono_db[module_name].insert(std::make_pair(config_name, 0));
        }
        else if (Repeated == type)
        {
            config_repeated_db[module_name].insert(std::make_pair(config_name, std::map<int, int>()));
        }
    }
    config_type_db[module_name][config_name] = type;
}

ConfigDB::ConfigType ConfigDB::retrieve_config_type(const std::string & module_name, const std::string & config_name)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_config_exists(module_name, config_name))
    {
        std::cout << "Config " << config_name << " need to register first!" << std::endl;
        return ConfigDB::Invalid;
    }

    return config_type_db[module_name][config_name];
}

void ConfigDB::update_config(const std::string & module_name, const std::string & config_name, int value)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_config_exists(module_name, config_name))
    {
        /*simple print*/
        // std::cout << "Config " << config_name << " need to register first!" << std::endl;
        // return;
        /*throw exception*/
        std::stringstream err;
        err << "Module " << module_name << " Config " << config_name << " need to register first!";
        throw Exception(err.str());
        /*auto register*/
        // register_config(module_name, config_name, Mono);
    }

    if (constraint_config_is_repeated(module_name, config_name))
    {
        // std::cout << "Repeated config " << config_name << " need address to update!" << std::endl;
        // return;
        std::stringstream err;
        err << "Module " << module_name << " Repeated config " << config_name
            << " need address to update! (please use the correct version of function)";
        throw Exception(err.str());
    }

    config_mono_db[module_name][config_name] = value;
}

void ConfigDB::update_config(const std::string & module_name, const std::string & config_name, int addr, int value)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_config_exists(module_name, config_name))
    {
        // std::cout << "Config " << config_name << " need to register first!" << std::endl;
        // return;
        std::stringstream err;
        err << "Module " << module_name << " Config " << config_name << " need to register first!";
        throw Exception(err.str());
        // register_config(module_name, config_name, Repeated);
    }

    if (constraint_config_is_mono(module_name, config_name))
    {
        // std::cout << "Mono config " << config_name << " don't need address!" << std::endl;
        // return;
        std::stringstream err;
        err << "Module " << module_name << " Mono config " << config_name
            << " don't need address! (please use the correct version of function)";
        throw Exception(err.str());
    }

    config_repeated_db[module_name][config_name][addr] = value;
}

void ConfigDB::reset_config(const std::string & module_name, const std::string & config_name)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_config_exists(module_name, config_name))
    {
        // std::cout << "Config " << config_name << " need to register first!" << std::endl;
        // return;
        std::stringstream err;
        err << "Module " << module_name << " Config " << config_name << " need to register first!";
        throw Exception(err.str());
        // register_config(module_name, config_name, Mono);
    }

    if (constraint_config_is_mono(module_name, config_name))
    {
        config_mono_db[module_name][config_name] = 0;
    }
    else if (constraint_config_is_repeated(module_name, config_name))
    {
        config_repeated_db[module_name][config_name] = std::map<int, int>();
    }
}

void ConfigDB::reset_config(const std::string & module_name, const std::string & config_name, int addr)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_config_exists(module_name, config_name))
    {
        // std::cout << "Config " << config_name << " need to register first!" << std::endl;
        // return;
        std::stringstream err;
        err << "Module " << module_name << " Config " << config_name << " need to register first!";
        throw Exception(err.str());
        // register_config(module_name, config_name, Repeated);
    }

    if (constraint_config_is_mono(module_name, config_name))
    {
        // std::cout << "Mono config " << config_name << " don't need address!" << std::endl;
        // return;
        std::stringstream err;
        err << "Module " << module_name << "Mono config " << config_name
            << " don't need address! (please use the correct version of function)";
        throw Exception(err.str());
    }

    config_repeated_db[module_name][config_name][addr] = 0;
}

int ConfigDB::retrieve_config(const std::string & module_name, const std::string & config_name)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_config_exists(module_name, config_name))
    {
        // std::cout << "Config " << config_name << " need to register first!" << std::endl;
        // return 0;
        std::stringstream err;
        err << "Module " << module_name << " Config " << config_name << " need to register first!";
        throw Exception(err.str());
        // register_config(module_name, config_name, Mono);
    }

    if (constraint_config_is_repeated(module_name, config_name))
    {
        // std::cout << "Repeated config " << config_name << " need address to retrieve!" << std::endl;
        // return 0;
        std::stringstream err;
        err << "Module " << module_name << " Repeated config " << config_name
            << " need address to retrieve! (please use the correct version of function)";
        throw Exception(err.str());
    }

    return config_mono_db[module_name][config_name];
}

int ConfigDB::retrieve_config(const std::string & module_name, const std::string & config_name, int addr)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_config_exists(module_name, config_name))
    {
        // std::cout << "Config " << config_name << " need to register first!" << std::endl;
        // return 0;
        std::stringstream err;
        err << "Module " << module_name << " Config " << config_name << " need to register first!";
        throw Exception(err.str());
        // register_config(module_name, config_name, Repeated);
    }

    if (constraint_config_is_mono(module_name, config_name))
    {
        // std::cout << "Mono config " << config_name << " don't need address!" << std::endl;
        // return 0;
        std::stringstream err;
        err << "Module " << module_name << " Mono config " << config_name
            << " don't need address! (please use the correct version of function)";
        throw Exception(err.str());
    }

    return config_repeated_db[module_name][config_name][addr];
}

void ConfigDB::retrieve_config_lines(const std::string & module_name, const std::string & config_name,
                                     std::vector<std::pair<int, int>> & list)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_module_exists(module_name))
    {
        std::stringstream err;
        err << "Module " << module_name << " don't exists!" << std::endl;
        throw Exception(err.str());
    }

    if (!constraint_config_exists(module_name, config_name))
    {
        std::stringstream err;
        err << "Config " << config_name << " need to register first!" << std::endl;
        throw Exception(err.str());
    }

    if (constraint_config_is_mono(module_name, config_name))
    {
        list.push_back(std::make_pair(0, config_mono_db[module_name][config_name]));
    }
    else if (constraint_config_is_repeated(module_name, config_name))
    {
        for (auto iter = config_repeated_db[module_name][config_name].begin();
             iter != config_repeated_db[module_name][config_name].end(); iter++)
        {
            list.push_back(*iter);
        }
    }
}

void ConfigDB::retrieve_module_list(std::vector<std::string> & list)
{
    std::lock_guard<std::mutex> guard(lock);
    for (auto iter = config_type_db.begin(); iter != config_type_db.end(); iter++)
    {
        list.push_back(iter->first);
    }
}

void ConfigDB::retrieve_config_list(const std::string & module_name, std::vector<std::string> & list)
{
    std::lock_guard<std::mutex> guard(lock);
    if (!constraint_module_exists(module_name))
    {
        std::stringstream err;
        err << "Module " << module_name << " Module " << module_name << " don't exists!";
        throw Exception(err.str());
    }

    for (auto iter = config_type_db[module_name].begin(); iter != config_type_db[module_name].end(); iter++)
    {
        list.push_back(iter->first);
    }
}

bool ConfigDB::constraint_module_exists(const std::string & module_name)
{
    return config_type_db.count(module_name) > 0;
}
bool ConfigDB::constraint_config_exists(const std::string & module_name, const std::string & config_name)
{
    return config_type_db[module_name].count(config_name) > 0;
}
bool ConfigDB::constraint_config_is_mono(const std::string & module_name, const std::string & config_name)
{
    return Mono == config_type_db[module_name][config_name];
}
bool ConfigDB::constraint_config_is_repeated(const std::string & module_name, const std::string & config_name)
{
    return Repeated == config_type_db[module_name][config_name];
}
