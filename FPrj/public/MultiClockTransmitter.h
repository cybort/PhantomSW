/*
 * @Description: Transmit long data with sop and eop
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:43:41
 */
#ifndef _MULTI_CLOCK_TRANSMITTER_H_
#define _MULTI_CLOCK_TRANSMITTER_H_
#include "systemc.h"
#include <iomanip>
#include <iostream>

class MultiClockSplitter
{
public:
    MultiClockSplitter() {}
    MultiClockSplitter(char *data, int length, int bandwidth) { init(data, length, bandwidth); }
    void init(const char *data, int length, int bandwidth)
    {
        start = data;
        remain_len = length;
        valid_sig = false;
        sop_sig = false;
        eop_sig = false;
        mod_sig = 0;
        bandw = bandwidth;
    }

    void next_step()
    {
        if (remain_len <= 0) /*finish*/
        {
            remain_len = 0;
            valid_sig = false;
            sop_sig = false;
            eop_sig = false;
            mod_sig = 0;
            return;
        }

        start += mod_sig; /*start from last split*/

        if (false == valid_sig) /*first clock*/
        {
            sop_sig = true;
        }
        else
        {
            sop_sig = false;
        }

        if (remain_len <= bandw) /*last clock*/
        {
            eop_sig = true;
            mod_sig = remain_len;
            remain_len = 0;
        }
        else /*long data continue*/
        {
            eop_sig = false;
            mod_sig = bandw;
            remain_len -= bandw;
        }
        valid_sig = true;
    }

    int bandwidth() { return bandw; }
    const char *current_pos() { return start; }
    int remain_length() { return remain_len; }
    bool valid() { return valid_sig; }
    bool sop() { return sop_sig; }
    bool eop() { return eop_sig; }
    int mod() { return mod_sig; }

protected:
    int bandw;
    const char *start;
    int remain_len;
    bool valid_sig;
    bool sop_sig;
    bool eop_sig;
    int mod_sig;
};

template <typename DATA_T> /*is_trivially_copyable*/
class MultiClockTransmitter
{
public:
    MultiClockTransmitter(sc_out<DATA_T> &_output, sc_out<bool> &_valid, sc_out<bool> &_sop, sc_out<bool> &_eop,
                          sc_out<int> &_mod, std::ostream &_os = std::cout)
        : splitter(), output(_output), valid(_valid), sop(_sop), eop(_eop), mod(_mod), debug(false), os(_os)
    {
    }

    void set_data(const char *data, int length) { splitter.init(data, length, sizeof(DATA_T)); }

    bool transmit_for_one_clock()
    {
        if (splitter.remain_length() <= 0)
        {
            return false;
        }
        splitter.next_step();
        if (debug)
        {
            print_status();
        }
        DATA_T temp;
        std::copy(splitter.current_pos(), splitter.current_pos() + splitter.mod(), reinterpret_cast<char *>(&temp));
        output.write(temp);
        valid.write(splitter.valid());
        sop.write(splitter.sop());
        eop.write(splitter.eop());
        mod.write(splitter.mod());
        return true;
    }

    void transmit_to_end()
    {
        while (transmit_for_one_clock())
        {
            if (debug)
            {
                os << "[" << std::right << std::setw(8) << sc_time_stamp() << std::left << std::setw(1) << "]"
                   << "===============================================" << endl;
            }
            wait();
        }
        clear_signal();
    }

    void transmit_to_end(const char *start, int length) // wait on last clock, transmit should be the last step, user
                                                        // don't need to wait after transmit to end
    {
        set_data(start, length);
        transmit_to_end();
    }

    void print_status()
    {
        os << "[" << std::right << std::setw(8) << sc_time_stamp() << std::left << std::setw(1) << "]" << std::boolalpha
           << "transmitter:    sop: " << splitter.sop() << " eop: " << splitter.eop() << " mod: " << splitter.mod()
           << " valid: " << splitter.valid() << endl;
    }

    void set_debug(bool b) { debug = b; }

    void clear_signal()
    {
        valid.write(false);
        sop.write(false);
        eop.write(false);
        mod.write(0);
    }

protected:
    MultiClockSplitter splitter;
    sc_out<DATA_T> &output;
    sc_out<bool> &valid;
    sc_out<bool> &sop;
    sc_out<bool> &eop;
    sc_out<int> &mod;

    std::ostream &os;
    bool debug;
};

#endif