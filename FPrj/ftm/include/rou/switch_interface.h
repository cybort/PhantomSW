/*
 * @Description: Cell related modules
 * @Author: f21538
 * @Date: 2020-11-27 18:12:15
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 14:27:45
 */
#include "CreditGrantConverter.h"
#include "CreditRequestConverter.h"
#include "cell_gen.h"
#include "cell_resolve.h"
#include "config.h"
#include "rx.h"
#include "systemc.h"
#include "testbench.h"
#include "tx.h"

SC_MODULE(switch_interface)
{
    bool debug;
    sc_in<bool> clk;

    sc_in<bool> pkt_valid_up, pkt_sop_up, pkt_eop_up;
    sc_in<int> pkt_mod_up;
    // sc_in<packet_line> packet_up;
    sc_in<data_bus> packet_up;
    sc_in<FlowStatusMessage> flow_status_in;
    sc_in<bool> valid_flow_status_in;
    sc_in<CreditInfo> credit_info_in;
    sc_in<bool> valid_credit_info_in;

    sc_out<bool> pkt_valid_down, pkt_sop_down, pkt_eop_down;
    sc_out<int> pkt_mod_down;
    // sc_out<packet_line> packet_down;
    sc_out<data_bus> packet_down;
    sc_out<FlowStatusMessage> flow_status_out;
    sc_out<bool> valid_flow_status_out;
    sc_out<CreditInfo> credit_info_out;
    sc_out<bool> valid_credit_info_out;
    sc_out<sc_bv<LINK_MAX>> link_valid_out;

    cell_gen cg;
    cell_resolve cr;
    rx r;
    tx t;
    CreditRequestConverter credit_request_converter;
    CreditGrantConverter credit_grant_converter;

    sc_signal<cell> tx_data[TM_CELL_PER_CLOCK_LIMIT], rx_data[TM_CELL_PER_CLOCK_LIMIT];
    sc_signal<bool> tx_valid[TM_CELL_PER_CLOCK_LIMIT], rx_valid[TM_CELL_PER_CLOCK_LIMIT];
    sc_signal<cell_flowsts> credit_request_up;
    sc_signal<bool> valid_credit_request_up;
    sc_signal<cell_credit> credit_grant_up;
    sc_signal<bool> valid_credit_grant_up;

    SC_CTOR(switch_interface)
        : cg("cell_gen"), cr("cell_resolve"), r("rx"), t("tx"), credit_request_converter("credit_request_converter"),
          credit_grant_converter("credit_grant_converter")
    {

        cg.debug = true;
        cg.clk(clk);
        cg.sop(pkt_sop_up);
        cg.eop(pkt_eop_up);
        cg.valid_pkt(pkt_valid_up);
        cg.packet(packet_up);
        cg.mod(pkt_mod_up);
        for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
        {
            cg.valid[i](tx_valid[i]);
            cg.data[i](tx_data[i]);
        }

        r.debug = true;
        r.clk(clk);
        for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
        {
            r.valid[i](rx_valid[i]);
            r.data[i](rx_data[i]);
        }
        r.flow_status_out(flow_status_out);
        r.valid_flow_status_out(valid_flow_status_out);
        r.credit_info_out(credit_info_out);
        r.valid_credit_info_out(valid_credit_info_out);

        cr.debug = true;
        cr.clk(clk);
        cr.sop(pkt_sop_down);
        cr.eop(pkt_eop_down);
        cr.pkt_valid(pkt_valid_down);
        cr.mod(pkt_mod_down);
        cr.pkt_out(packet_down);
        for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
        {
            cr.valid[i](rx_valid[i]);
            cr.data[i](rx_data[i]);
        }

        t.debug = true;
        t.clk(clk);
        for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
        {
            t.valid[i](tx_valid[i]);
            t.data[i](tx_data[i]);
        }
        t.credit_request(credit_request_up);
        t.valid_credit_request(valid_credit_request_up);
        t.credit_grant(credit_grant_up);
        t.valid_credit_grant(valid_credit_grant_up);
        t.link_valid_out(link_valid_out);

        credit_request_converter.debug = true;
        credit_request_converter.clk(clk);
        credit_request_converter.flow_status(flow_status_in);
        credit_request_converter.valid_flow_status(valid_flow_status_in);
        credit_request_converter.cell_request(credit_request_up);
        credit_request_converter.valid_cell_request(valid_credit_request_up);

        credit_grant_converter.debug = true;
        credit_grant_converter.clk(clk);
        credit_grant_converter.credit_info(credit_info_in);
        credit_grant_converter.valid_credit_info(valid_credit_info_in);
        credit_grant_converter.cell_grant(credit_grant_up);
        credit_grant_converter.valid_cell_grant(valid_credit_grant_up);
    }
};
