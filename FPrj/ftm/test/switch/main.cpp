#include "sw.h"

int sc_main(int argc, char* argv[])
{
	//cout<<"cell size: "<<sizeof(cell)<<endl;
    //getchar();
  sc_clock	clk("clk", sc_time(20, SC_NS));
    sc_signal <bool> d_sw_valid[SW_LINK_NUM], u_sw_valid[SW_LINK_NUM];
    sc_signal <cell> d_sw_data[SW_LINK_NUM], u_sw_data[SW_LINK_NUM];

	sw s("switch");
	s.clk(clk);
 
    for(int i = 0; i < SW_LINK_NUM; i++)
    {
        s.d_valid[i](d_sw_valid[i]);
        s.d_data[i](d_sw_data[i]);
        s.u_valid[i](u_sw_valid[i]);
        s.u_data[i](u_sw_data[i]);
    }

	//sc_start(sc_time(2000, SC_MS));
	sc_start();

	return 0;
}
