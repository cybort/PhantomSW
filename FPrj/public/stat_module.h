/*
 * @Description: Print counter every clock
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-04 13:37:43
 */
#ifndef _STAT_MODULE_H_
#define _STAT_MODULE_H_

#include "ModuleLog.h"
#include "StatCounter.h"
#include "systemc.h"

SC_MODULE(stat_module)
{
    bool debug;
    sc_in<bool> clk;

    ModuleLog log;

    SC_CTOR(stat_module) : log(name()), debug(true)
    {
        SC_METHOD(print_counter);
        sensitive << clk.pos();
    }

    void print_counter()
    {
        std::vector<std::string> module_name_list;
        StatCounterBase::GetInstance().retrieve_module_list(module_name_list);
        for (auto iter = module_name_list.begin(); iter != module_name_list.end(); iter++)
        {
            std::string module = *iter;
            std::vector<std::string> counter_name_list;
            StatCounterBase::GetInstance().retrieve_counter_list(module, counter_name_list);

            for (auto iter_counter = counter_name_list.begin(); iter_counter != counter_name_list.end(); iter_counter++)
            {
                std::string counter = *iter_counter;
                StatCounterBase::CounterType type =
                    StatCounterBase::GetInstance().retrieve_counter_type(module, counter);

                if (StatCounterBase::Mono == type)
                {
                    log.prefix() << "Module: " << std::setw(30) << module << " Counter: " << std::setw(30) << counter
                                 << " Value: " << StatCounterBase::GetInstance().retrieve_counter(module, counter)
                                 << std::endl;
                }
                else if (StatCounterBase::Repeated == type)
                {
                    std::vector<std::pair<int, int>> lines;
                    StatCounterBase::GetInstance().retrieve_counter_lines(module, counter, lines);
                    // log.prefix() << "Module: " << std::setw(30) << module << " Counter: " << std::setw(30) << counter
                    //             << " Size: " << lines.size() << std::endl;
                    for (auto iter_lines = lines.begin(); iter_lines != lines.end(); iter_lines++)
                    {
                        int num = iter_lines->second;
                        if (num != 0)
                        {
                            log.prefix() << "Module: " << std::setw(30) << module << " Counter: " << std::setw(30)
                                         << counter << " Addr: " << iter_lines->first << " Value: " << num << std::endl;
                        }
                    }
                }
            }
            // log.prefix()<<"=========module=================split=================="<<std::endl;
        }
        log.prefix() << "=========clock=================split==================" << std::endl;
    }
};

#endif
