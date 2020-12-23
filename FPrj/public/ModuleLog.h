/*
 * @Description: Print log by module
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:41:51
 */
#ifndef _MODULE_LOG_H_
#define _MODULE_LOG_H_

#include "systemc.h"
#include "ConfigResolver.h"
#include <fstream>
#include <iomanip>
#include <iostream>

class ModuleLog : public fstream
{
public:
    ModuleLog(const std::string &s, int line_limit = 10000){ ModuleLog(s.c_str(), line_limit); }
    ModuleLog(const char *s, int line_limit = 10000) : module_name(s), lines_limit(line_limit), lines(0), enable_line_limit(ConfigResolver::GetInstance().get_bool("log", "enable_line_limit", true))
    {
        open((std::string("./[log]") + s + std::string(".log")).c_str(), std::ios::out | std::ios::trunc);
        if (!is_open())
        {
            std::cout << "open file failed!" << endl;
            getchar();
        }
    }
    virtual ~ModuleLog()
    {
        if (is_open())
        {
            close();
        }
    }
    ModuleLog &prefix()
    {
        if (enable_line_limit && ++lines > lines_limit)
        {
            lines = 0;
            close();
            open((std::string("./[log]") + module_name + std::string(".log")).c_str(), std::ios::out | std::ios::trunc);
        }
        *this << "[" << std::right << std::setw(8) << sc_time_stamp() << std::left << std::setw(1) << "]";
        return *this;
    }

protected:
    std::string module_name;
    int lines_limit;
    bool enable_line_limit;
    int lines;
};

#endif