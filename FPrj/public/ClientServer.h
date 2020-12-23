/*
 * @Description: Client and server with short connect
 * @Author: f21538
 * @Date: 2020-11-30 16:15:30
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:38:33
 */
#ifndef _CLIENTSERVER_H
#define _CLIENTSERVER_H
#include "QueueSocketHandler.h"
#include "base64.h"
#include "cell.h"
#include <ISocketHandler.h>
#include <TcpSocket.h>
#include <iostream>
class ClientSocket : public TcpSocket
{
public:
    ClientSocket(ISocketHandler &h, const char *s, int s_size) : TcpSocket(h), m_data(s, s_size) { SetLineProtocol(); }

    ~ClientSocket() {}

    void OnConnect()
    {
        // printf("on connect\n");
        std::string encoded = base64_encode(reinterpret_cast<const unsigned char *>(m_data.c_str()), m_data.length());
        Send(encoded + "\n");
        // SetCloseAndDelete();
    }

    void OnLine(const std::string &line)
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

private:
    std::string m_data;
};

template <typename T> class ServerSocket : public TcpSocket
{
public:
    ServerSocket(ISocketHandler &h) : TcpSocket(h), handler(dynamic_cast<QueueSocketHandler<T> *>(&h))
    {
        SetLineProtocol();
    }

    ~ServerSocket() {}

    void OnLine(const std::string &line)
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
            handler->push(temp);
            SetCloseAndDelete();
        }
        else
        {
            SetCloseAndDelete();
        }
    }

private:
    QueueSocketHandler<T> *handler;
};

template <> class ServerSocket<cell> : public TcpSocket
{
public:
    ServerSocket(ISocketHandler &h) : TcpSocket(h), handler(dynamic_cast<QueueSocketHandler<cell> *>(&h))
    {
        SetLineProtocol();
    }

    ~ServerSocket() {}

    void OnLine(const std::string &line)
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
            handler->push(temp);
            SetCloseAndDelete();
        }
        else
        {
            SetCloseAndDelete();
        }
    }

private:
    QueueSocketHandler<cell> *handler;
};

#endif // _CLIENTSERVER_H_
