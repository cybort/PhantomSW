#include "pd.h"

void sc_trace(sc_trace_file *tf, const pd& p, const sc_string& name)
{
//    char *dat = p.get_data();
//	for (int i = 0; i < MAX_PD_SIZE; i++)
//        sc_trace(tf, dat[i], name + ".pddat");
}

bool pd::set_flowID(unsigned fID)
{
    if(fID > 0x3ffff)
        return false;

    this->flowID = fID;

    return true;
}

unsigned pd::get_flowID() const
{
    return this->flowID;
}

bool pd::set_length(unsigned len)
{
    if(len > 0x3fff)
        return false;

    this->length = len;

    return true;
}

unsigned pd::get_length() const
{
    return this->length;
}

bool pd::set_addr(unsigned addr)
{
    if(addr > 0xffffffff)
        return false;

    this->address = addr;

    return true;
}

unsigned pd::get_addr() const
{
    return this->address;
}

bool pd::set_result(bool reslt)
{
    this->result = reslt;

    return true;
}

bool pd::get_result() const
{
    return this->result;
}

char* pd::get_data()
{
    char *dat = this->data;
    return dat;
}