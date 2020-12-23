#ifndef _SW_H_
#define _SW_H_

#include "cell.h"
#include "port.h"
#include "tlm_utils/tlm_quantumkeeper.h"
#include "ClientServerLong.h"
#include "QueueSocketHandler.h"
#include <ListenSocket.h>
#include <SocketHandler.h>


class sw: public sc_module
{
    SC_HAS_PROCESS(sw);
public:
    sc_in<bool>	clk;
    
    sc_in<bool> d_valid[SW_LINK_NUM];
    sc_in<cell> d_data[SW_LINK_NUM];
    sc_out<bool> u_valid[SW_LINK_NUM];
    sc_out<cell> u_data[SW_LINK_NUM];

    sw(sc_module_name name);
    ~sw()
    {
        for (int i = 0; i < SEND_SOCKETS_NUM; i++)
        {
            delete cc[i];
        }
    }

private:
    tlm_utils::tlm_quantumkeeper ukeeper, dkeeper;
    QueueSocketHandler<cell> uh, dh;
    //ClientSocketLong<cell>* cc[LISTEN_SOCKETS_NUM];
    std::vector<ClientSocketLong<cell>* > cc;

    void rx();
    void sch();
    void socket();
    void tx();

};

#endif
