/*
 * @Description:
 * @Author: f21538
 * @Date: 2020-11-30 16:15:30
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:39:56
 */
#include "clock_step.h"

void clock_step::per_clock()
{
    std::string input = "";
    if (debug)
    {
        std::cout << "Current clock: " << current_clock << std::endl;
    }
    log.prefix() << "Current clock: " << current_clock << " Remain clock: " << clocks_remain << std::endl;

    ++current_clock;

    if (Step == step_mode)
    {
        --clocks_remain;
        if (clocks_remain <= 0)
        {
            std::cout << "Please input num of clocks for next step:" << std::endl;
            while (input.empty())
            {
                std::getline(std::cin, input);
                if (input.empty())
                {
                    clocks_remain = 1;
                    break;
                }
                else
                {
                    input.erase(std::remove_if(input.begin(), input.end(), not_a_digit), input.end());
                    if (!input.empty())
                    {
                        std::istringstream stream(input);
                        stream >> clocks_remain;
                    }
                }
            }

            /*if (std::cin.peek() == '\n')
            {
                std::cin.ignore();
                clocks_remain = 1;
            }
            else
            {
                while(!(std::cin >> clocks_remain))
                {
                    std::cout<<"Invalid input."<<std::endl;
                }
            }*/
        }
    }
}