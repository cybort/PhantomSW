/*
 * @Author: your name
 * @Date: 2020-11-26 14:00:38
 * @LastEditors: duyang
 * @LastEditTime: 2020-12-01 09:45:22
 * @Description: file content
 */
#ifndef _STREAM_H_
#define _STREAM_H_
#define _SEC_ 1000000
#define _LOAD_RES_ 1000000
#include "Packet.h"
#include "list.h"
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

struct Stream
{
    bool streamtype;
    bool mix;
    unsigned burst;
    unsigned loadpersec;
    unsigned TM_ID;
    List<IPacket> packet_list;
    bool run;
    bool quit_thread;
    pthread_t pth;

    Stream();
    void reset(void);
    void stream_thread(void);
    void thread_stop(void);

    void operator=(Stream & D)
    {
        streamtype = D.streamtype;
        mix = D.mix;
        burst = D.burst;
        loadpersec = D.loadpersec;
        TM_ID = D.TM_ID;
        for (int i = 0; i < D.packet_list.size(); i++)
        {
            packet_list.add(D.packet_list.find(i)->data);
        }
    }
};

int Gap(Stream * ST)
{
    int gap = 1;
    std::string payload;
    if (false == ST->mix)
    {
        payload = ST->packet_list.find(0)->data.get_payload();
    }
    else
    {
        for (int i = 0; i < ST->packet_list.size(); i++)
        {
            payload += ST->packet_list.find(i)->data.get_payload();
        }
    }

    if (ST->streamtype == 0)
    {
        gap = ST->loadpersec * _LOAD_RES_ / payload.size() * 8;
        if (gap == 0)
        {
            std::cout << "  loadpersec < packet/sec ! " << std::endl;
            gap = 1;
        }
        gap = _SEC_ / gap;
        if (ST->mix == true)
        {
            gap = gap / 4;
        }
    }
    else
    {
        gap = _SEC_ / ST->loadpersec;
        if (gap == 0)
        {
            std::cout << "burst loadpersec is beyond 1 packet/usec ! switch to 100/sec " << std::endl;
            gap = 10000;
        }
    }

    return gap;
}

void send_packet(ISocketHandler & h, const char * str, int str_size, const char * ip, int port)
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

void * run_sendstream(void * args)
{
    int round = 0;
    int ret = 0, i = 0;
    long t = 0;
    SocketHandler h;
    //   XmlParse<T> xml;
    int packetGap = 1;
    std::string packet = "adb";
    //   std::string payload;
    Stream * ST = (Stream *)args;
    struct timeval tv_s, tv_e;

    packet = ST->packet_list.find(0)->data.get_bytes();
    while (!ST->quit_thread)
    {

        if (ST->run == true)
        {
            packetGap = Gap(ST);
            std::cout << ">>"
                      << "gap :" << packetGap << std::endl;
            std::cout << ">>"
                      << "sending..." << std::endl;
            while ((ST->burst > round) || (ST->streamtype == 0))
            {
                gettimeofday(&tv_s, NULL);
                if (ST->mix == true)
                {
                    i = round % (ST->packet_list.size());
                    packet = ST->packet_list.find(i)->data.get_bytes();
                }
                round++;
                send_packet(h, packet.c_str(), packet.size(), LOCALHOST, STREAM_SEND_PORT + ST->TM_ID);
                if (ST->run == 0)
                {
                    std::cout << ">>"
                              << "stoping" << std::endl;
                    break;
                }
                gettimeofday(&tv_e, NULL);
                t = tv_e.tv_usec - tv_s.tv_usec;
                std::cout << ">>"
                          << "time:" << t << std::endl;
                if ((packetGap > t) && (t > 0))
                {
                    packetGap = packetGap - t;
                    usleep(packetGap);
                }
                else
                {
                    std::cout << ">>"
                              << "gap is too short !" << std::endl;
                    continue;
                }
                gettimeofday(&tv_e, NULL);
                t = tv_e.tv_usec - tv_s.tv_usec;
                std::cout << ">>"
                          << "time all:" << t << std::endl;
            }
            if (round >= ST->burst)
            {
                std::cout << " " << round << " packets sent " << std::endl;
            }

            ST->run = false;
            round = 0;
            std::cout << "stopped" << std::endl;
        }
        /*
                if (load == true)
                {
                    std::cout << "loading..." << std::endl;
                    load = false;
                    //          ST->reset();
                    //          ret = xml.parse_xml(&ST);
                    //           packet = ST->pktdata.get_bytes();
                    //           packetGap = Gap(ST);
                    std::cout << "load ok" << std::endl;
                }
        */
        sleep(1);
    }

    std::cout << "thread stopped " << std::endl;
    pthread_exit(NULL);
}

void Stream::stream_thread() { int ret = pthread_create(&pth, NULL, run_sendstream, this); }

void Stream::thread_stop()
{
    this->quit_thread = true;
    pthread_join(this->pth, NULL);
}

Stream::Stream()
{
    run = false;
    quit_thread = false;
    streamtype = 0;
    mix = 0;
    burst = 0;
    loadpersec = 0;
    TM_ID = 0;
}

void Stream::reset(void)
{
    run = false;
    quit_thread = false;
    streamtype = 0;
    mix = 0;
    burst = 0;
    loadpersec = 0;
    TM_ID = 0;
    if (packet_list.size() > 0)
    {
        packet_list.removeAll();
    }
}

#endif