/*
 * @Description:
 * @Author: f21538
 * @Date: 2020-11-27 18:12:14
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-28 15:41:53
 */
#include "testbench.h"
#include <cstdlib>
/*void testbench::clear_signal()
{
    sop.write(false);
    eop.write(false);
    valid_pkt.write(false);
    mod.write(0);
}*/

/*void testbench::send_pkt()
{
    int packet_num = 200;
    stat.update_counter("init_packet_num", packet_num);
    wait();
    for (int j = 0; j < packet_num; j++)
    {

        int length = 1024;//rand()%(1024-64)+64;
        std::string p(length, static_cast<char>(rand()%('z'-'!')+'!'));
        std::cout<<"sending pkt "<<j<<" "<<length<<endl;

        tx.transmit_to_end(p.data(), p.size());
    }

    for (int i = 0; i < 20; i++) wait();
    //sc_stop();

}*/

void testbench::recv_pkt_up()
{
    while (true)
    {
        rx_up.receive_to_end();
        stat.increase_counter("up_from_nif_packet_num", 1);
        wait();
    }
}

void testbench::recv_pkt_down()
{
    while (true)
    {
        rx_down.receive_to_end();
        stat.increase_counter("down_to_nif_packet_num", 1);
        // if (stat.retrieve_counter("received_packet_num") == 100) // stat.retrieve_counter("init_packet_num"))
        //{
        //    wait();
        //    sc_stop();
        //}
        wait();
    }
}
