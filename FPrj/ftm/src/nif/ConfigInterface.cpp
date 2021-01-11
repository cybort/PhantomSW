#include "ConfigInterface.h"

void ConfigInterface::connect()
{
    clientSocket->Open(HOST_IP, HOST_PORT);
    handler.Add(clientSocket);
    int tm_id = _TM_ID_;
    handler.Select(0, 500);
    clientSocket->SendBuf((char *)&tm_id, sizeof(tm_id));

    if (handler.GetCount())
    {
        std::cout << "Host connect success!" << std::endl;
    }
    for (;;)
    {
        try
        {
            handler.Select(0, 500);
            if (!clientSocket->IsConnected() || !handler.GetCount())
            {
                delete clientSocket;
                clientSocket = new ClientSocketLong<std::string>(handler, false);
                clientSocket->Open(HOST_IP, HOST_PORT);
                handler.Add(clientSocket);
                handler.Select(0, 500);
                clientSocket->SendBuf((char *)&tm_id, sizeof(tm_id));
                if (handler.GetCount())
                {
                    std::cout << "Host reconnect success!" << std::endl;
                }
            }
        }
        catch (Exception & e)
        {
            std::cout << "Exception: " << e.ToString() << std::endl << "Stack: " << std::endl << e.Stack() << std::endl;
        }
        wait();
    }
}

void ConfigInterface::decode(const std::string request, HOST_MSG_TYPE & type, std::string & module_name,
                             std::string & config_name, int & addr, int & value)
{
    HOST_MSG_HEADER msg_header;
    std::stringstream request_stream(request.substr(sizeof(HOST_MSG_HEADER), request.size() - sizeof(HOST_MSG_HEADER)));
    std::string request_segment;
    std::vector<std::string> request_seglist;

    msg_header = *(HOST_MSG_HEADER *)request.substr(0, sizeof(HOST_MSG_HEADER)).data();
    type = msg_header.uiMsgType;
    while (std::getline(request_stream, request_segment, '#'))
    {
        request_seglist.push_back(request_segment);
    }
    if (type == MSG_ID_HOST_WRITE)
    {
        switch (request_seglist.size())
        {
        case 4:
        {
            module_name = request_seglist[0];
            config_name = request_seglist[1];
            value = *(int *)request_seglist[2].data();
            break;
        }
        case 5:
        {
            module_name = request_seglist[0];
            config_name = request_seglist[1];
            addr = *(int *)request_seglist[2].data();
            value = *(int *)request_seglist[3].data();
            break;
        }
        default:
            throw Exception("command error: wrong command length!");
            break;
        }
    }
    else if (type == MSG_ID_HOST_READ)
    {
        switch (request_seglist.size())
        {
        case 3:
        {
            module_name = request_seglist[0];
            config_name = request_seglist[1];
            break;
        }
        case 4:
        {
            module_name = request_seglist[0];
            config_name = request_seglist[1];
            addr = *(int *)request_seglist[2].data();
            break;
        }
        default:
            throw Exception("command error: wrong command length!");
            break;
        }
    }
    else
    {
        throw Exception("command error: only support set/get command!");
    }
}

void ConfigInterface::set_config(std::string module_name, std::string config_name, int addr, int value)
{
    this->ret_info = "";
    try
    {
        if (addr >= 0)
        {
            ConfigDB::GetInstance().update_config(module_name, config_name, addr, value);
            std::cout << "set:"
                      << " "
                      << " " << module_name << ", "
                      << " " << config_name << ", "
                      << "addr:"
                      << " " << addr << ", "
                      << "value: " << value << "." << std::endl;
            this->ret_info = "set success!";
        }
        else
        {
            ConfigDB::GetInstance().update_config(module_name, config_name, value);
            std::cout << "set:"
                      << " "
                      << " " << module_name << ", "
                      << " " << config_name << ", "
                      << "value: " << value << "." << std::endl;
            this->ret_info = "set success!";
        }
    }
    catch (Exception & e)
    {
        this->ret_info = e.ToString();
    }
}

void ConfigInterface::get_config(std::string module_name, std::string config_name, int addr, int value)
{
    this->ret_info = "";

    try
    {
        if (addr >= 0)
        {
            value = ConfigDB::GetInstance().retrieve_config(module_name, config_name, addr);
            std::cout << "get:"
                      << " "
                      << " " << module_name << ", " << config_name << ", "
                      << "addr:"
                      << " " << addr << ", "
                      << "value: " << value << "." << std::endl;
            ret_info = "get" + module_name + " " + "," + " " + config_name + "," + " " + "addr:" + " " +
                       std::to_string(addr) + "," + " " + "value:" + " " + std::to_string(value) + ".";
        }
        else
        {
            value = ConfigDB::GetInstance().retrieve_config(module_name, config_name);
            std::cout << "get:"
                      << " "
                      << " " << module_name << ", "
                      << " " << config_name << ", "
                      << "value: " << value << "." << std::endl;
            ret_info = "get" + module_name + " " + "," + " " + config_name + "," + " " + "value:" + " " +
                       std::to_string(value) + ".";
        }
    }
    catch (Exception & e)
    {
        this->ret_info = e.ToString();
        std::cout << e.ToString() << std::endl;
    }
}

void ConfigInterface::recv()
{
    std::string request;
    HOST_MSG_TYPE type;
    std::string module_name;
    std::string config_name;
    int addr = -1;
    int value = 0;
    while (clientSocket->receive_pop_if_not_empty(request))
    {
        if (request.size() == sizeof(int))
        {
            if (*(int *)request.data() == MSG_ID_HOST_RETURN_ERROR)
            {
                throw Exception("regist error: TM ID is in used!");
            }
            if (*(int *)request.data() == MSG_ID_HOST_RETURN_OK)
            {
                std::cout << "regist success!" << std::endl;
                continue;
            }
        }
        try
        {
            decode(request, type, module_name, config_name, addr, value);
        }
        catch (Exception & e)
        {
            this->ret_info = e.ToString();
        }

        switch (type)
        {
        case MSG_ID_HOST_WRITE:
        {
            set_config(module_name, config_name, addr, value);
        }
        case MSG_ID_HOST_READ:
        {
        }
        default:
            get_config(module_name, config_name, addr, value);
        }
    }
}

void ConfigInterface::trans()
{
    if (this->ret_info.size())
    {
        HOST_MSG_HEADER header;
        header.uiSize = ret_info.size();
        ret_info = std::string(header.bytes, header.bytes + sizeof(header)) + ret_info;
        clientSocket->SendBuf(this->ret_info.c_str(), ret_info.size());
        ret_info = "";
    }
}