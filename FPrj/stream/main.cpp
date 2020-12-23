#include "ClientServer.h"
#include "cstring"
#include "port.h"
#include "systemc.h"
#include "tlm_utils/tlm_quantumkeeper.h"
#include "unistd.h"
#include "xmlparse.h"
#include <SocketHandler.h>
#include <cstdlib>
#include <iostream>
#include <pthread.h>

STREAM_S ST;

bool quit_app = false;
bool run = false;
bool load = false;

int Gap()
{
    int gap = 1;
    std::string payload;
    payload = ST.pktdata.get_payload();

    if (ST.streamtype == 0)
    {
        gap = ST.loadpersec * _LOAD_RES_ / payload.size() * 8;
        if (gap == 0)
        {
            std::cout << "  loadpersec < packet/sec ! " << std::endl;
            gap = 1;
        }
        gap = _SEC_ / gap;
    }
    else
    {
        gap = _SEC_ / ST.loadpersec;
        if (gap == 0)
        {
            std::cout << "burst loadpersec is beyond 1 packet/usec ! switch to 100/sec " << std::endl;
            gap = 10000;
        }
    }

    return gap;
}

void send_data(ISocketHandler &h, const char *str, int str_size, const char *ip, int port)
{
    sc_time period(1, SC_MS);
    ClientSocket cc(h, str, str_size);
    cc.Open(ip, port);
    std::cout << "tx:send to " << port << std::endl;

    h.Add(&cc);

    h.Select(0, 1);

    while (h.GetCount())
    {
        h.Select(0, 1);
    }

    return;
}

void *run_sendstream(void *args)
{
    int round = 0;
    int ret = 0;
    SocketHandler h;
    XmlParse xml;
    int packetGap = 1;
    std::string packet;
    std::string payload;

    packet = ST.pktdata.get_bytes();

    std::cout << "pkt :" << packet << " packet size :" << packet.size() << "  tm id : " << ST.TM_ID << std::endl;

    packetGap = Gap();
    std::cout << "gap : " << packetGap << std::endl;

    while (!quit_app)
    {
        if (run == true)
        {
            std::cout << ">>"
                      << "sending..." << std::endl;
            while ((ST.burst > round) || (ST.streamtype == 0))
            {
                round++;
                send_data(h, packet.c_str(), packet.size(), LOCALHOST, STREAM_SEND_PORT + ST.TM_ID);
                if (run == 0)
                {
                    std::cout << ">>"
                              << "stoping" << std::endl;
                    break;
                }
                usleep(packetGap);
            }
            if (round >= ST.burst)
            {
                std::cout << " " << round << " packets sent " << std::endl;
            }

            run = false;
            round = 0;
            std::cout << "stopped" << std::endl;
        }

        if (load == true)
        {
            std::cout << "loading..." << std::endl;
            load = false;
            ST.reset();
            ret = xml.parse_xml(&ST);
            packet = ST.pktdata.get_bytes();
            packetGap = Gap();
            std::cout << "load ok" << std::endl;
        }

        if (quit_app)
        {
            pthread_exit(NULL);
        }

        sleep(2);
    }

    return NULL;
}

int sc_main(int argc, char *argv[])
{
    int ret = 0;
    std::string opt;
    pthread_t pth;
    XmlParse xml;

    ST.reset();

    ret = xml.parse_xml(&ST);
    if (ret != 0)
        return -1;

    ret = pthread_create(&pth, NULL, run_sendstream, NULL);

    usleep(1000);
    std::cout << std::endl
              << "send pakcet input 'run'/'r' ; stop send input 'stop'/'s' ; reload packet input 'load'/'s' ;exit "
                 "input 'quit'/'q' "
              << std::endl
              << ">>";
    while (!quit_app)
    {
        getline(cin, opt);
        if (opt == "run" || opt == "r")
        {
            run = true;
        }
        else if (opt == "stop" || opt == "s")
        {
            if (run == false)
            {
                std::cout << "already stopped ! " << std::endl << ">>";
            }
            else
            {
                run = false;
            }
        }
        else if (opt == "load" || opt == "l")
        {
            load = true;
        }
        else if (opt == "help" || opt == "h")
        {
            std::cout << "send pakcet input 'run'/'r' ; stop send input 'stop'/'s' ; reload packet input 'load'/'s' "
                         ";exit input 'quit'/'q' "
                      << std::endl
                      << ">>";
        }
        else if (opt == "quit" || opt == "q")
        {
            quit_app = true;
            std::cout << "ready to exit ! " << std::endl;
        }
        else
        {
            std::cout << ">>";
        }
    }

    pthread_join(pth, NULL);
    return 0;
}
