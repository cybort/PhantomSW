/*
 * @Description:
 * @Author: f21538
 * @Date: 2020-12-15 17:45:59
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-15 17:46:08
 */

#ifndef _CREDIT_REQUEST_CONVERTER_H_
#define _CREDIT_REQUEST_CONVERTER_H_

#include "FlowStatusMessage.h"
#include "cell.h"

SC_MODULE(CreditRequestConverter)
{
    bool debug;
    sc_in<bool> clk;
    sc_in<FlowStatusMessage> flow_status;
    sc_in<bool> valid_flow_status;

    sc_out<cell_flowsts> cell_request;
    sc_out<bool> valid_cell_request;

    void convert();
    int current_seq;

    SC_CTOR(CreditRequestConverter) : current_seq(0), debug(false)
    {
        SC_THREAD(convert);
        sensitive << clk.pos();
    }
};
#endif
