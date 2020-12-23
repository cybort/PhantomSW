/*
 * @Description: Receive long data between sop and eop
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:42:51
 */
#ifndef _MULTI_CLOCK_RECEIVER_
#define _MULTI_CLOCK_RECEIVER_
#include "systemc.h"
#include <iomanip>
#include <iostream>

template <typename DATA_T> class MultiClockReceiver
{
public:
    bool started;
    MultiClockReceiver(sc_in<DATA_T> &_input, sc_in<bool> &_valid, sc_in<bool> &_sop, sc_in<bool> &_eop,
                       sc_in<int> &_mod, std::ostream &_os = std::cout)
        : input(_input), valid(_valid), sop(_sop), eop(_eop), mod(_mod), debug(false), recv_data(""), os(_os),
          started(false)
    {
    }

    bool receive_one_clock()
    {
        if (debug && valid.read() == true)
        {
            print_status();
        }
        if (sop.read() == true)
        {
            recv_data = "";
            started = true;
        }
        if (valid.read() == true && true == started)
        {
            DATA_T temp = input.read();
            if (mod.read() > sizeof(DATA_T) || mod.read() < 0)
            {
                if (debug)
                {
                    os << "[" << std::right << std::setw(8) << sc_time_stamp() << std::left << std::setw(1) << "]"
                       << "received mod incorrect!" << std::endl;
                }
                return false;
            }
            recv_data += std::string(reinterpret_cast<char *>(&temp), mod.read());
        }
        if (eop.read() == true)
        {
            started = false;
            return false;
        }
        else
        {
            return true;
        }
    }

    bool try_receive_to_end()
    {
        if (valid.read() == false)
        {
            return false;
        }

        while (receive_one_clock())
        {
            if (debug)
            {
                os << "[" << std::right << std::setw(8) << sc_time_stamp() << std::left << std::setw(1) << "]"
                   << "********************************************" << std::endl;
            }
            wait();
        }
        if (debug)
        {
            os << "[" << std::right << std::setw(8) << sc_time_stamp() << std::left << std::setw(1) << "]"
               << "********************************************" << std::endl;
        }
        return true;
    }

    void receive_to_end() // will not wait on last clock, in order to process data, user need to wait themselves after
                          // data-processing!
    {
        bool received = try_receive_to_end();
        while (received == false)
        {
            wait();
            received = try_receive_to_end();
        }
    }

    std::string &result() { return recv_data; }

    void print_status()
    {
        os << "[" << std::right << std::setw(8) << sc_time_stamp() << std::left << std::setw(1) << "]" << std::boolalpha
           << "receiver:    sop: " << sop.read() << " eop: " << eop.read() << " mod: " << mod.read()
           << " valid: " << valid.read() << endl;
    }

    void set_debug(bool b) { debug = b; }

protected:
    std::string recv_data;
    sc_in<DATA_T> &input;
    sc_in<bool> &valid;
    sc_in<bool> &sop;
    sc_in<bool> &eop;
    sc_in<int> &mod;

    std::ostream &os;
    bool debug;
};

#endif