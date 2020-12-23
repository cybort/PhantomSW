/*
 * @Description: Client and server with long connect
 * @Author: f21538
 * @Date: 2020-11-30 16:15:30
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-17 11:45:20
 */
#ifndef _CLIENTSERVER_H
#define _CLIENTSERVER_H
#include "ModuleLog.h"
#include "QueueSocketHandler.h"
#include "base64.h"
#include "cell.h"
#include <ISocketHandler.h>
#include <Ipv4Address.h>
#include <TcpSocket.h>
#include <Utility.h>
#include <iostream>
#include <queue>

template <typename T> class ClientSocketLong : public TcpSocket
{
public:
    ClientSocketLong(ISocketHandler & h) : TcpSocket(h), isConnected(false), debug(false) { SetLineProtocol(); }

    ~ClientSocketLong() { SetCloseAndDelete(); }
    /*
    bool Open(const std::string &host,port_t port)
    {
        ipaddr_t l;
            if (!Utility::u2ip(host,l))
            {
                SetCloseAndDelete();
                return false;
            }
            Ipv4Address ad(l, port);
            Ipv4Address local;
            return TcpSocket::Open(ad, local);
    }*/

    void OnConnect()
    {
        isConnected = true;
        printf("on connect\n");
        // std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(m_data.c_str()), m_data.length());
        // Send(encoded + "\n");
        // SetCloseAndDelete();
        /*
        sc_time period(60, SC_MS);
        while(true)
        {
            T c;
            while(pop_if_not_empty(c))
            {
                std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(c.raw_data), sizeof(c));
                Send(encoded + "\n");
            }
            //tlmwait();
            keeper.inc(period);
            if (keeper.need_sync())
               keeper.sync();
        }*/
    }

    void OnLine(const std::string & line)
    {
        // SetCloseAndDelete();

        std::string decoded = base64_decode(line);
        if (decoded.size())
        {
            // printf("Reply from server: '%s'\n",decoded.c_str());
        }
        else
        {
            // Send("\n");
            // SetCloseAndDelete();  //close on empty line(only "\n")
        }
    }
    void OnConnectTimeout() { std::cout << "timeout" << std::endl; }
    void SendWithEncode(const char * s, int s_size)
    {
        // std::cout<< "prepare to send ";//<<"cell id: " << ((cell*)s)->cell_id << " packet id: " <<
        // ((cell*)s)->packet_id << " type: " << ((cell*)s)->type <<endl;
        //((cell*)s)->dump_header("prepare to send ");
        // std::cout<<endl;
        std::string encoded = base64_encode(reinterpret_cast<const unsigned char *>(s), s_size);
        push(encoded);
        if (isConnected)
        {
            std::string send_s;
            while (pop_if_not_empty(send_s))
            {
                Send(send_s + "\n");
                if (debug)
                {
                    //((T *)(base64_decode(send_s).c_str()))->dump_header("sending");
                    std::cout << "sending" << base64_decode(send_s) << std::endl;
                }
            }
        }
    }
    void push(std::string & s) { q.push(s); }

    bool pop_if_not_empty(std::string & s)
    {
        if (q.empty())
        {
            return false;
        }

        s = q.front();
        q.pop();
        return true;
    }

    int size() { return q.size(); }
    bool debug;

private:
    std::queue<std::string> q;
    bool isConnected;
};

template <typename T, typename Container = std::queue<T> > class ServerSocketLong : public TcpSocket
{
public:
    ServerSocketLong(ISocketHandler & h) : TcpSocket(h), handler(dynamic_cast<QueueSocketHandler<T, Container> *>(&h))
    {
        SetLineProtocol();
    }

    ~ServerSocketLong() { SetCloseAndDelete(); }

    void OnLine(const std::string & line)
    {
        std::string decoded = base64_decode(line);
        if (decoded.size())
        {
            // printf("receive from client: '%s'\n",decoded.c_str());
            // std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(decoded.c_str()),
            // decoded.length());
            T temp(decoded);
            // memcpy(temp.raw_data, decoded.c_str(), decoded.size());
            // Send("\n");//confirm received
            // if (!temp.is_empty())
            //{
            handler->push(temp);
            // std::cout<<"server received: ";//packet id: "<<temp.packet_id<<"  cell id:
            // "<<temp.cell_id<<std::endl; temp.dump_header(); std::cout<<endl;;
            //}
            // SetCloseAndDelete();
        }
        else
        {
            // SetCloseAndDelete();
        }
    }

private:
    QueueSocketHandler<T, Container> * handler;
};

/*Specialized Template*/
template <> class ClientSocketLong<cell> : public TcpSocket
{
public:
    ClientSocketLong(ISocketHandler & h) : TcpSocket(h), isConnected(false), debug(false) { SetLineProtocol(); }

    ~ClientSocketLong() { SetCloseAndDelete(); }
    /*
    bool Open(const std::string &host,port_t port)
    {
        ipaddr_t l;
            if (!Utility::u2ip(host,l))
            {
                SetCloseAndDelete();
                return false;
            }
            Ipv4Address ad(l, port);
            Ipv4Address local;
            return TcpSocket::Open(ad, local);
    }*/

    void OnConnect()
    {
        isConnected = true;
        printf("on connect\n");
        // std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(m_data.c_str()), m_data.length());
        // Send(encoded + "\n");
        // SetCloseAndDelete();
        /*
        sc_time period(60, SC_MS);
        while(true)
        {
            T c;
            while(pop_if_not_empty(c))
            {
                std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(c.raw_data), sizeof(c));
                Send(encoded + "\n");
            }
            //tlmwait();
            keeper.inc(period);
            if (keeper.need_sync())
               keeper.sync();
        }*/
    }

    void OnLine(const std::string & line)
    {
        // SetCloseAndDelete();

        std::string decoded = base64_decode(line);
        if (decoded.size())
        {
            // printf("Reply from server: '%s'\n",decoded.c_str());
        }
        else
        {
            // Send("\n");
            // SetCloseAndDelete();  //close on empty line(only "\n")
        }
    }
    void OnConnectTimeout() { std::cout << "timeout" << endl; }
    void SendWithEncode(const char * s, int s_size)
    {
        // std::cout<< "prepare to send ";//<<"cell id: " << ((cell*)s)->cell_id << " packet id: " <<
        // ((cell*)s)->packet_id << " type: " << ((cell*)s)->type <<endl;
        //((cell*)s)->dump_header("prepare to send ");
        // std::cout<<endl;
        std::string encoded = base64_encode(reinterpret_cast<const unsigned char *>(s), s_size);
        push(encoded);
        if (isConnected)
        {
            std::string send_s;
            while (pop_if_not_empty(send_s))
            {
                Send(send_s + "\n");
                if (debug)
                {
                    ((cell *)(base64_decode(send_s).c_str()))->dump_header("sending");
                }
            }
        }
    }
    void push(std::string & s) { q.push(s); }

    bool pop_if_not_empty(std::string & s)
    {
        if (q.empty())
        {
            return false;
        }

        s = q.front();
        q.pop();
        return true;
    }

    int size() { return q.size(); }
    bool debug;

private:
    std::queue<std::string> q;
    bool isConnected;
};

template <typename Container> class ServerSocketLong<cell, Container> : public TcpSocket
{
public:
    ServerSocketLong(ISocketHandler & h)
        : TcpSocket(h), handler(dynamic_cast<QueueSocketHandler<cell, Container> *>(&h)) //, log("server")
    {
        SetLineProtocol();
    }

    ~ServerSocketLong() { SetCloseAndDelete(); }

    void OnLine(const std::string & line)
    {
        std::string decoded = base64_decode(line);
        if (decoded.size())
        {
            // printf("receive from client: '%s'\n",decoded.c_str());
            // std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(decoded.c_str()),
            // decoded.length());
            cell temp;
            memcpy(temp.raw_data, decoded.c_str(), decoded.size());
            // Send("\n");//confirm received
            if (!temp.is_empty())
            {
                handler->push(temp);
                // std::cout<<"server received: ";//packet id: "<<temp.packet_id<<"  cell id:
                // "<<temp.cell_id<<std::endl; temp.dump_header(); std::cout<<endl;;
            }
            else
            {
                // temp.dump(log.prefix());
            }
            // SetCloseAndDelete();
        }
        else
        {
            // SetCloseAndDelete();
        }
    }

private:
    // ModuleLog log;
    QueueSocketHandler<cell, Container> * handler;
};

#endif // _CLIENTSERVER_H_
