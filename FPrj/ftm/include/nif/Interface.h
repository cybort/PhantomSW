/*
 * @Author: duyang
 * @Date: 2020-11-30 09:20:24
 * @LastEditors: duyang
 * @LastEditTime: 2020-11-30 16:34:47
 * @Description: file content
 */

#ifndef _VIRTUAL_H_
#define _VIRTUAL_H_

#include "ModuleLog.h"
#include "MultiClockReceiver.h"
#include "MultiClockTransmitter.h"
#include "Packet.h"
#include "config.h"
#include "pd.h"
#include "port.h"
#include "queue"

SC_MODULE(Interface)
{
    /* vif -> pd queue manager */
    sc_in<bool>         clk;
    sc_out<bool>        validSlice_out;
    sc_out<bool>        sop_out;
    sc_out<bool>        eop_out;
    sc_out<int>         mod_out;
    sc_out<data_bus>    sls_out;
    sc_in<bool>         packet_read;

    /* vid -> wred */
    sc_out<pd>          pd_out;
    sc_out<bool>        valid_pd;
    sc_in<bool>         wred_rd;

    /* vtc -> vif */
    std::queue<FPacket> recv_packet_fifo;
    std::queue<pd>      pdFifo;
    /* -> vif
        sc_in<bool>         validSlice_in;
        sc_in<bool>         sop_in;
        sc_in<bool>         eop_in;
        sc_in<int>          mod_in;
        sc_in<data_bus>     sls_in;
    */

    /* common */
    MultiClockTransmitter<data_bus> tr;
    //   MultiClockReceiver<data_bus>    re;
    ModuleLog log;

    void recv_from_tc();
    void qin_request();
    void send_to_qcu();
    void recv_from_tm();

    SC_CTOR(Interface) : tr(sls_out, validSlice_out, sop_out, eop_out, mod_out), log(name())
    //                   re(sls_in, validSlice_in, sop_in, eop_in, mod_in)
    {
        SC_THREAD(recv_from_tc);
        sensitive << clk.pos();
        SC_THREAD(qin_request);
        sensitive << clk.pos();
        SC_THREAD(send_to_qcu);
        sensitive << clk.pos();
        //       SC_THREAD(recv_from_tm);
        //       sensitive << clk.pos();
    }
};

#endif