/*
 * @Author: duyang
 * @Date: 2020-11-07 10:06:20
 * @LastEditTime: 2020-11-26 16:58:56
 * @LastEditors: duyang
 * @Description: In User Settings Edit
 */

#include "Interface.h"
#include "ClientServer.h"
#include <ListenSocket.h>
#include <SocketHandler.h>
#include <stdlib.h>

void Interface::recv_from_tc()
{
    IPacket             pkt_temp1;
    FPacket             pkt_temp3;
    std::string         str, str1;
    IHeader             itmh;
    FHeader             ftmh;
    IHeader::Type       type;
    unsigned            tmp;
    pd                  tmppd;
    QueueSocketHandler<std::string>             h;
    ListenSocket<ServerSocket<std::string> >    *sockets; 

    sockets = new ListenSocket<ServerSocket<std::string> >(h);
    if (sockets->Bind(STREAM_SEND_PORT, 20))
    {
        exit(-1);
    }

    std::cout << "nif rx:bind socket" << std::endl;
    h.Add(sockets);
    h.Select(0, 1);

    while (h.GetCount())
    {
        h.Select(0, 1);

        //if(h.size()> 4 && h.pop_if_not_empty(str))
        if (h.pop_if_not_empty(str))
        {
            do
            {
                log.prefix() << "start to recieve pakcet ! " << std::endl;
                if (recv_packet_fifo.size() < 10)
                {
                    pkt_temp1.set_bytes(str);
                    str1 = pkt_temp1.get_payload();

                    itmh = pkt_temp1.get_itmh();
                    type = itmh.get_type();
                    ftmh.set_packet_size(str1.size());
                    ftmh.set_ver(_TM_ID_);
                    ftmh.set_src_tm_id(_VERSION_);

                    if (type == IHeader::TDM)
                    {
                        ftmh.set_type(FHeader::TDM_UNICAST);
                        log.prefix() << "packet type : ITMH_TDM " << std::endl;
                    }
                    else if (type == IHeader::MULTICAST)
                    {
                        ftmh.set_type(FHeader::MULTICAST);
                        tmp = itmh.get_multicast_id();
                        ftmh.set_multicast_id(tmp);
                        tmp = itmh.get_tc();
                        ftmh.set_tc(tmp);
                        tmp = itmh.get_dp();
                        ftmh.set_dp(tmp);
                        tmp = itmh.get_cal_len_index();
                        ftmh.set_cal_len(tmp);
                        log.prefix() << "packet type : ITMH_MULTICAST " << std::endl;
                    }
                    else if (type == IHeader::UNICAST)
                    {
                        ftmh.set_type(FHeader::UNICAST);
                        tmp = itmh.get_tc();
                        ftmh.set_tc(tmp);
                        tmp = itmh.get_dp();
                        ftmh.set_dp(tmp);
                        tmp = itmh.get_cal_len_index();
                        ftmh.set_cal_len(tmp);
                        log.prefix() << "packet type : ITMH_UNICAST " << std::endl;

                        tmp = itmh.get_flow_id();
                        tmppd.set_flowID(tmp);
                        log.prefix() << " flowID : " << tmp << endl;
                    }
                    else
                    {
                        log.prefix() << "TYPE ERROR: " << type << std::endl;
                        continue;
                    }

                    pkt_temp3.set_ftmh(ftmh);
                    pkt_temp3.set_payload(str1);
                    recv_packet_fifo.push(pkt_temp3);

                    tmppd.set_length(str.size());
                    pdFifo.push(tmppd);
                }
                else
                {
                    log.prefix() << "recv fifo full ! " << std::endl;
                }

                log.prefix() << "rx:received done:" << std::endl;
            } while (h.pop_if_not_empty(str));
        }

        wait();
    }

    delete sockets;
}

void Interface::send_to_qcu()
{
    std::string     pkt_str;
    int             ret = 0;

    while (true)
    {
        if (packet_read.read() == true)
        {
            if (true)
            {
                if (recv_packet_fifo.empty())
                {
                    log.prefix() << "vif to qm fifo empty !" << std::endl;
                    wait();
                    continue;
                }

                pkt_str = recv_packet_fifo.front().get_bytes();
                recv_packet_fifo.pop();
                tr.transmit_to_end(pkt_str.data(), pkt_str.size());
                log.prefix() << "vif send pkt to qm !" << std::endl;
            }
        }
        else
        {
            wait();
        }
    }
}

void Interface::qin_request()
{
    while (true)
    {
        valid_pd.write(false);

        if (wred_rd.read() == true)
        {
            if (pdFifo.empty() != true)
            {
                pd_out.write(pdFifo.front());
                pdFifo.pop();
                valid_pd.write(true);
                log.prefix() << " queue in request ! " << std::endl;
            }
            else
            {
                //               std::cout << "pd fifo empty" << std::endl;
            }
        }

        wait();
    }
}

void Interface::recv_from_tm()
{
    /*
    FPacket recv_packet;
    re.set_debug(true);
    while (true)
    {
        re.receive_to_end();
        recv_packet.set_bytes(re.result());
        std::cout<<"receive data:" << re.result() <<std::endl;
        wait();
    }
    */
}
