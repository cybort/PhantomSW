/*
 * @Author: your name
 * @Date: 2020-11-30 09:20:24
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-21 10:40:57
 * @Description: file content
 */

#ifndef _BUFFER_MANAGER_H_
#define _BUFFER_MANAGER_H_

#include "Fifo.hpp"
#include "ModuleLog.h"
#include "MultiClockReceiver.h"
#include "MultiClockTransmitter.h"
#include "Packet.h"
#include "config.h"
#include "systemc.h"
#include <map>
#include <queue>

SC_MODULE(BufferManager)
{
    sc_in<bool> clk;
    /*packet in*/
    sc_in<data_bus> packet_in;
    sc_in<bool> packet_in_valid;
    sc_in<bool> packet_in_sop;
    sc_in<bool> packet_in_eop;
    sc_in<int> packet_in_mod;
    /*packet out*/
    sc_out<data_bus> packet_out;
    sc_out<bool> packet_out_valid;
    sc_out<bool> packet_out_sop;
    sc_out<bool> packet_out_eop;
    sc_out<int> packet_out_mod;
    /*read logic addr in*/
    sc_in<unsigned> read_logic_addr_in;
    sc_in<bool> read_logic_addr_in_valid;
    /*save logic addr in*/
    sc_in<unsigned> write_logic_addr_in;
    /*save complete signal out*/
    sc_out<bool> write_complete_signal_out;
    /*read complete signal out*/
    sc_out<bool> read_complete_signal_out;

    MultiClockTransmitter<data_bus> trs;
    MultiClockReceiver<data_bus> recv;

    Fifo<FPacket> packet_in_fifo;
    Fifo<FPacket> packet_out_fifo;
    Fifo<unsigned> write_logic_addr_in_fifo;

    std::map<unsigned, FPacket> dram;
    ModuleLog log;

    void recv_packet();
    void save_packet();
    void read_packet();
    void trans_packet();

    SC_CTOR(BufferManager)
        : trs(packet_out, packet_out_valid, packet_out_sop, packet_out_eop, packet_out_mod),
          recv(packet_in, packet_in_valid, packet_in_sop, packet_in_eop, packet_in_mod), log(name())
    {
        SC_THREAD(recv_packet);
        sensitive << clk.pos();
        SC_THREAD(trans_packet);
        sensitive << clk.pos();
        SC_METHOD(save_packet);
        sensitive << clk.pos();
        SC_METHOD(read_packet);
        sensitive << clk.pos();
    }
};

#endif