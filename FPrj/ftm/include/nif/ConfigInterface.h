#ifndef CONFIG_INTERFACE_H
#define CONFIG_INTERFACE_H

#include "ClientServerLong.h"
#include "ConfigDB.h"
#include "Exception.h"
#include "HostMsgHeader.h"
#include "ListenSocket.h"
#include "config.h"
#include "port.h"
#include "systemc.h"
#include <QueueSocketHandler.h>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

SC_MODULE(ConfigInterface)
{
    sc_in<bool> clk;
    QueueSocketHandler<std::string> handler;
    ClientSocketLong<std::string> * clientSocket;
    std::string ret_info;
    void connect();
    void recv();
    void trans();
    void set_config(std::string module_name, std::string config_name, int addr, int value);
    void get_config(std::string module_name, std::string config_name, int addr, int value);
    void decode(std::string command, HOST_MSG_TYPE & type, std::string & module_name, std::string & config_name,
                int & addr, int & value);
    SC_CTOR(ConfigInterface)
    {
        SC_THREAD(connect);
        sensitive << clk.pos();
        SC_METHOD(recv);
        sensitive << clk.pos();
        SC_METHOD(trans);
        sensitive << clk.pos();
        clientSocket = new ClientSocketLong<std::string>(handler, false);
    };
    ~ConfigInterface() { delete clientSocket; }
};

#endif