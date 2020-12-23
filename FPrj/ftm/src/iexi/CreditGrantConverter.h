#ifndef _CREDIT_GRANT_CONVERTER_H_
#define _CREDIT_GRANT_CONVERTER_H_

#include "CreditInfo.h"
#include "ModuleLog.h"
#include "cell.h"

SC_MODULE(CreditGrantConverter)
{
    bool debug;
    sc_in<bool> clk;
    sc_in<CreditInfo> credit_info;
    sc_in<bool> valid_credit_info;
    
    sc_out<cell_credit> cell_grant;
    sc_out<bool> valid_cell_grant;
    
    ModuleLog log;
    
    void convert();
    
    SC_CTOR(CreditGrantConverter) : debug(false), log(name())
    {
        SC_THREAD(convert);
        sensitive << clk.pos();
    }
};
#endif