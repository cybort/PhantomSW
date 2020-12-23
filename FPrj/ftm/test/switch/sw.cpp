#include "sw.h"

#include <string.h>
#include <strings.h>
#include <sstream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <fcntl.h>

#define LISTEN_WINDOW_SIZE 10
#define QUEUE_SIZE 3

sw::sw(sc_module_name name) : sc_module(name), cc(SEND_SOCKETS_NUM)
{
    tlm_utils::tlm_quantumkeeper::set_global_quantum(sc_time(10, SC_MS));
    ukeeper.reset();
    dkeeper.reset();
    /*
    for (int i = 0; i < LISTEN_SOCKETS_NUM; i++)
    {
        cc[i] = new ClientSocketLong<cell>(dh);
    }*/

    SC_THREAD(rx);
    sensitive << clk.neg();
    SC_METHOD(sch);
    sensitive << clk.neg();
    SC_THREAD(socket);
    sensitive << clk.neg();
    SC_THREAD(tx);
    sensitive << clk.neg();
    
    
}

void sw::rx()
{
    
    sc_time period(1, SC_MS);
    ListenSocket<ServerSocketLong<cell> > *sockets[LISTEN_SOCKETS_NUM];
    while(true)
    {
        try{
            for (int i = 0; i < LISTEN_SOCKETS_NUM; i++)
            {
                sockets[i] = new ListenSocket<ServerSocketLong<cell> >(uh);
                //std::cout<<"rx:create socket"<< i <<std::endl;
                if(sockets[i]->Bind(SW_BASE_SERVER_PORT+i, LISTEN_WINDOW_SIZE))
                {
                    exit(-1);
                }
                //std::cout<<"rx:bind socket"<< i <<std::endl;
                uh.Add(sockets[i]);
                std::cout<<"swrx:add socket"<< i <<std::endl;
            }
        }
        catch (Exception& e)
        {
            std::cout<<"Exception: "<<e.ToString()<<std::endl<<"Stack: "<<std::endl<<e.Stack()<<std::endl;
        }
        uh.Select(0,1);
        //std::cout<<"rx:select"<<std::endl;
        //cell temp_old;
        while (uh.GetCount())
        {
            uh.Select(0,1);
            //if(uh.size() > 0) std::cout<<"swrx:size "<<uh.size()<<std::endl;
            /*cell temp;
            if(uh.size()>= QUEUE_SIZE && uh.pop_if_not_empty(temp))
            {
                do
                {
                    //std::cout<<(temp==temp_old?"Dup":"Not dup")<<std::endl;
                    //temp_old = temp;
                    std::cout<<"rx:received packet id: "<<temp.packet_id<<" cell id: "<<temp.cell_id<<std::endl;
                    uh.push(temp);
                } while(uh.pop_if_not_empty(temp));
            }*/
            //std::cout<<"rx:before wait"<<std::endl;
            //wait();
            ukeeper.inc(period);
            if (ukeeper.need_sync())
                ukeeper.sync();
            //continue;
        }
     
        for(int i = 0; i < LISTEN_SOCKETS_NUM; i++)
        {
            delete sockets[i];
        }
        wait();
    }
}

void sw::sch()
{
    cell temp;
    if(uh.size() > 0 && uh.pop_if_not_empty(temp))
    {
        do
        {
            if(!temp.is_empty())
            {
                dh.push(temp);
                std::cout<<"sch:";//packet id: "<<temp.packet_id<<" cell id: "<<temp.cell_id<<" type "<<temp.type<<std::endl;
                temp.dump_header();
                std::cout<<endl;
            }
            
        }while(uh.size()>= QUEUE_SIZE && uh.pop_if_not_empty(temp));
    }
}

void sw::socket()
{
    sc_time period(1, SC_MS);
    while (true)
    {
        std::cout<<"press any key after ftm start"<<endl;
        getchar();
        
        for (int i = 0; i < SEND_SOCKETS_NUM; i++)
        {
            //std::cout<<"Socket "<<i<<" connect "<<((cc[i]->Open(LOCALHOST, TM_BASE_SERVER_PORT+i))==true)<<endl;
            cc[i] = new ClientSocketLong<cell>(dh);
            cc[i]->Open(LOCALHOST, TM_BASE_SERVER_PORT+i);
            dh.Add(cc[i]);
        }

    
        dh.Select(0,1);
        //std::cout<<"tx:connect "<<port<<std::endl;
        while (dh.GetCount())
        {
            dh.Select(0,1);
            //wait();
            dkeeper.inc(period);
            if (dkeeper.need_sync())
               dkeeper.sync();
            //continue;
        }
        std::cout<<" no socket connected"<<std::endl;
        
        for (int i = 0; i < SEND_SOCKETS_NUM; i++)
        {
            delete cc[i];
        }
        
    }
}

void sw::tx()
{
    for(int i = 0;;)
    {

        cell c;
        if (dh.size() > 0 && dh.pop_if_not_empty(c))
        {
            do
            {
                std::cout<<"swtx:send ";//packet id: "<<c.packet_id<<"    cell id: "<<c.cell_id<<"    port: "<<TM_BASE_SERVER_PORT+i<<std::endl;
                c.dump_header();
                std::cout<<endl;
                //send_data(dh, c.raw_data, sizeof(c), LOCALHOST, TM_BASE_SERVER_PORT+i);
                cc[i]->SendWithEncode(c.raw_data, sizeof(c));
                i = (i+1)%SEND_SOCKETS_NUM;
            }while(dh.size()>= QUEUE_SIZE && dh.pop_if_not_empty(c));
        }
        else
        {
            //wait();
            dkeeper.inc(sc_time(1, SC_MS));
            if (dkeeper.need_sync())
                dkeeper.sync();
        }
        
        //wait();

    }
}

