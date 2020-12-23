/*
 * @Description: Counter database
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-18 10:38:41
 */
#ifndef _STAT_CONFIGDB_H_
#define _STAT_CONFIGDB_H_
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class ConfigDB
{
public:
    enum ConfigType
    {
        Mono,
        Repeated,
        Invalid
    };

    static ConfigDB & GetInstance()
    {
        static ConfigDB instance;
        return instance;
    }

    void register_config(const std::string & module_name, const std::string & config_name, ConfigType type);
    ConfigType retrieve_config_type(const std::string & module_name, const std::string & config_name);
    void update_config(const std::string & module_name, const std::string & config_name, int value); /*for mono*/
    void update_config(const std::string & module_name, const std::string & config_name, int addr,
                       int value);                                                       /*for repeated*/
    void reset_config(const std::string & module_name, const std::string & config_name); /*for mono & repeated*/
    void reset_config(const std::string & module_name, const std::string & config_name, int addr);   /*for repeated*/
    int retrieve_config(const std::string & module_name, const std::string & config_name);           /*for mono*/
    int retrieve_config(const std::string & module_name, const std::string & config_name, int addr); /*for repeated*/
    int retrieve_config_size(const std::string & module_name, const std::string & config_name);      /*for repeated*/

    template <typename StringsContainer> StringsContainer & retrieve_module_list(StringsContainer & list);
    template <typename StringsContainer>
    StringsContainer & retrieve_config_list(const std::string & module_name, StringsContainer & list);

protected:
    std::mutex lock;
    bool constraint_module_exists(const std::string & module_name);
    bool constraint_config_exists(const std::string & module_name, const std::string & config_name);
    bool constraint_config_is_mono(const std::string & module_name, const std::string & config_name);
    bool constraint_config_is_repeated(const std::string & module_name, const std::string & config_name);

private:
    ConfigDB() {}
    ConfigDB(const ConfigDB &) {}
    ConfigDB & operator=(const ConfigDB &) {}

    std::map<std::string /*module_name*/, std::map<std::string /*register_name*/, ConfigType> > config_type_db;
    std::map<std::string /*module_name*/, std::map<std::string /*register_name*/, int /*value*/> > config_mono_db;
    std::map<std::string /*module_name*/,
             std::map<std::string /*register_name*/, std::map<int /*addr*/, int /*value*/> > >
        config_repeated_db;
};

class ConfigAccesssor /*design for bind to sc_module*/
{
public:
    ConfigAccesssor(const std::string & module_name) : module(module_name) {}

    void register_config(const std::string & config_name, ConfigDB::ConfigType type = ConfigDB::Mono)
    {
        ConfigDB::GetInstance().register_config(module, config_name, type);
    }

    ConfigDB::ConfigType retrieve_config_type(const std::string & config_name)
    {
        return ConfigDB::GetInstance().retrieve_config_type(module, config_name);
    }

    void update_config(const std::string & config_name, int value)
    {
        ConfigDB::GetInstance().update_config(module, config_name, value);
    }

    void update_config(const std::string & config_name, int addr, int value)
    {
        ConfigDB::GetInstance().update_config(module, config_name, addr, value);
    }

    void reset_config(const std::string & config_name) { ConfigDB::GetInstance().reset_config(module, config_name); }

    void reset_config(const std::string & config_name, int addr)
    {
        ConfigDB::GetInstance().reset_config(module, config_name, addr);
    }

    int retrieve_config(const std::string & config_name)
    {
        return ConfigDB::GetInstance().retrieve_config(module, config_name);
    }

    int retrieve_config(const std::string & config_name, int addr)
    {
        return ConfigDB::GetInstance().retrieve_config(module, config_name, addr);
    }

    int retrieve_config_size(const std::string & config_name)
    {
        return ConfigDB::GetInstance().retrieve_config_size(module, config_name);
    }

private:
    std::string module;
};

#endif
