#include "ClientServer.h"
#include "cstring"
#include "port.h"
#include "stream.h"
//#include "tlm_utils/tlm_quantumkeeper.h"
#include "list.h"
#include "unistd.h"
#include "xmlparse.h"
#include <SocketHandler.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char * argv[])
{
    int ret = 0;
    std::string opt;

    XmlParse<List<Stream> > xml;
    List<Stream> st_list;

    ret = xml.parse_xml(st_list);
    if (ret != 0)
    {
        std::cout << " parse error ! " << std::endl;
        return -1;
    }
    std::cout << " here ! " << st_list.find(0)->data.TM_ID << std::endl;
    std::cout << std::endl << st_list.size() << ":" << st_list.find(0)->data.packet_list.size();

    for (int i = 0; i < st_list.size(); i++)
    {
        st_list.find(i)->data.stream_thread();
    }

    usleep(1000);
    std::cout << std::endl
              << "send pakcet input 'run'/'r' ; stop send input 'stop'/'s' ; reload packet input 'load'/'s' ;exit "
                 "input 'quit'/'q' "
              << std::endl
              << ">>";
    while (true)
    {
        getline(cin, opt);
        if (opt.substr(0,3) == "run" || opt.substr(0,1) == "r")
        {
            for (int i = 0; i < st_list.size(); i++)
            {
                st_list.find(i)->data.run = true;
            }
        }
        else if (opt.substr(0,4)== "stop" || opt.substr(0,1) == "s")
        {
            for (int i = 0; i < st_list.size(); i++)
            {
                st_list.find(i)->data.run = false;
            }
        }
        else if (opt.substr(0,4) == "load" || opt.substr(0,1) == "l")
        {
            for (int i = 0; i < st_list.size(); i++)
            {
                st_list.find(i)->data.thread_stop();
            }

            ret = xml.parse_xml(st_list);
            if (ret != 0)
            {
                std::cout << " parse error ! " << std::endl;
                return -1;
            }

            for (int i = 0; i < st_list.size(); i++)
            {
                st_list.find(i)->data.stream_thread();
            }
        }
        else if (opt.substr(0,4) == "help" || opt.substr(0,1) == "h")
        {
            std::cout << "send pakcet input 'run'/'r' ; stop send input 'stop'/'s' ; reload packet input 'load'/'s' "
                         ";exit input 'quit'/'q' "
                      << std::endl
                      << ">>";
        }
        else if (opt.substr(0,4)  == "quit" || opt.substr(0,1)  == "q")
        {
            std::cout << "ready to exit ! " << std::endl;
            break;
        }
        else
        {
            std::cout << ">>";
        }
    }

    for (int i = 0; i < st_list.size(); i++)
    {
        st_list.find(i)->data.thread_stop();
    }


    return 0;
}
