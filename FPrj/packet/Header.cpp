#include "Header.h"

#define ITMH_TYPE_LENGTH 2
#define CHANNEL_NO_LENGTH 10
#define TC_LENGTH 3
#define DP_LENGTH 3
#define MULTICAST_ID_LENGTH 18
#define CAL_LEN_INDEX_LENGTH 5
#define FLOW_ID_LENGTH 17

#define FTMH_TYPE_LENGTH 2
#define VER_LENGTH 2
#define PACKET_SIZE_LENGTH 14
#define SRC_TM_ID_LENGTH 11
#define OUT_PORT_LENGTH 10
#define CAL_LEN_LENGTH 9

#define OTMH_TYPE_LENGTH 2
#define PORT_NO_LENGTH 8
#define MC_GPI_LENGTH 22

IHeader::IHeader() { memset(this->bytes, 0, sizeof(char) * sizeof(this->field)); }

void IHeader::set_type(enum IHeader::Type type) { this->field.type = type; }

IHeader::Type IHeader::get_type() { return this->field.type; }

void IHeader::set_channel_no(unsigned channel_no)
{
    if (this->field.type != IHeader::TDM)
    {
        throw Exception("error : Type must be TDM.");
    }
    else if (channel_no >= 1 << CHANNEL_NO_LENGTH)
    {
        throw Exception("error : channel_no is out of rang.");
    }
    else
    {
        this->field.dest_info.tdm.channel_no = channel_no;
    }
}

unsigned IHeader::get_channel_no()
{
    if (this->field.type != IHeader::TDM)
    {
        throw Exception("error : Type must be TDM.");
    }
    else
    {
        return this->field.dest_info.tdm.channel_no;
    }
}

void IHeader::set_tc(unsigned tc)
{
    if (tc >= 1 << TC_LENGTH)
    {
        throw Exception("error : tc is out of rang.");
    }
    else
    {
        switch (this->field.type)
        {
        case IHeader::UNICAST:
            this->field.dest_info.unicast.tc = tc;
            break;
        case IHeader::MULTICAST:
            this->field.dest_info.multicast.tc = tc;
            break;
        default:
            throw Exception("error : Type must be Unicast/Multicast.");
            break;
        }
    }
}

unsigned IHeader::get_tc()
{
    switch (this->field.type)
    {
    case IHeader::UNICAST:
        return this->field.dest_info.unicast.tc;
        break;
    case IHeader::MULTICAST:
        return this->field.dest_info.multicast.tc;
        break;
    default:
        throw Exception("error : Type must be Unicast/Multicast.");
        break;
    }
}

void IHeader::set_dp(unsigned dp)
{
    if (dp >= 1 << DP_LENGTH)
    {
        throw Exception("error : dp is out of rang.");
    }
    else
    {
        switch (this->field.type)
        {
        case IHeader::MULTICAST:
            this->field.dest_info.multicast.dp = dp;
            break;
        case IHeader::UNICAST:
            this->field.dest_info.unicast.dp = dp;
            break;
        default:
            throw Exception("error : Type must be Unicast/Multicast.");
            break;
        }
    }
}

unsigned IHeader::get_dp()
{
    switch (this->field.type)
    {
    case IHeader::MULTICAST:
        return this->field.dest_info.multicast.dp;
        break;
    case IHeader::UNICAST:
        return this->field.dest_info.unicast.dp;
        break;
    default:
        throw Exception("error : Type must be Unicast/Multicast.");
        break;
    }
}

void IHeader::set_multicast_id(unsigned multicast_id)
{
    if (multicast_id >= 1 << MULTICAST_ID_LENGTH)
    {
        throw Exception("error : multicast_id is out of rang.");
    }
    else
    {
        switch (this->field.type)
        {
        case IHeader::MULTICAST:
            this->field.dest_info.multicast.multicast_id = multicast_id;
            break;
        default:
            throw Exception("error : Type must be Multicast.");
            break;
        }
    }
}

unsigned IHeader::get_multicast_id()
{
    switch (this->field.type)
    {
    case IHeader::MULTICAST:
        return this->field.dest_info.multicast.multicast_id;
        break;
    default:
        throw Exception("error : Type must be Multicast.");
        break;
    }
}

void IHeader::set_cal_len_index(unsigned cal_len_index)
{
    if (cal_len_index >= 1 << CAL_LEN_INDEX_LENGTH)
    {
        throw Exception("error : cal_len_index is out of rang.");
    }
    else
    {
        switch (this->field.type)
        {
        case IHeader::UNICAST:
            this->field.dest_info.unicast.cal_len_index = cal_len_index;
            break;
        default:
            throw Exception("error : Type must be Unicast.");
            break;
        }
    }
}

unsigned IHeader::get_cal_len_index()
{
    switch (this->field.type)
    {
    case IHeader::UNICAST:
        return this->field.dest_info.unicast.cal_len_index;
        break;
    default:
        throw Exception("error : Type must be Unicast.");
        break;
    }
}

void IHeader::set_flow_id(unsigned flow_id)
{
    if (flow_id >= 1 << FLOW_ID_LENGTH)
    {
        throw Exception("error : flow_id is out of rang.");
    }
    else
    {
        switch (this->field.type)
        {
        case IHeader::UNICAST:
            this->field.dest_info.unicast.flow_id = flow_id;
            break;
        default:
            throw Exception("error : Type must be Unicast.");
            break;
        }
    }
}

unsigned IHeader::get_flow_id()
{
    switch (this->field.type)
    {
    case IHeader::UNICAST:
        return this->field.dest_info.unicast.flow_id;
        break;
    default:
        throw Exception("error : Type must be Unicast.");
        break;
    }
}

std::string IHeader::get_bytes() { return std::string(this->bytes, sizeof(field)); }

void IHeader::set_bytes(std::string bytes)
{
    if (bytes.size() != sizeof(field))
    {
        throw Exception("error : size is not equal to ITMH.");
    }
    std::copy(bytes.c_str(), bytes.c_str() + bytes.size(), this->bytes);
}

int IHeader::get_size() { return sizeof(field); }

void IHeader::dump()
{
    std::cout << "IHeader:"
              << " ";
    if (this->field.type == IHeader::EMPTY)
    {
        std::cout << "Empty header." << endl;
    }
    if (this->field.type == IHeader::TDM)
    {
        std::cout << "TDM header,"
                  << " ";
        std::cout << "Field,"
                  << " ";
        std::cout << "Channel no:"
                  << " " << this->field.dest_info.tdm.channel_no << ". " << endl;
    }
    if (this->field.type == IHeader::MULTICAST)
    {
        std::cout << "Multicast Header,"
                  << " ";
        std::cout << "Field,"
                  << " ";
        std::cout << "DP:"
                  << " " << this->field.dest_info.multicast.dp << ", ";
        std::cout << "Multicast ID:"
                  << " " << this->field.dest_info.multicast.multicast_id << ", ";
        std::cout << "TC:"
                  << " " << this->field.dest_info.multicast.tc << ". " << endl;
    }
    if (this->field.type == IHeader::UNICAST)
    {
        std::cout << "Unicast Header,"
                  << " ";
        std::cout << "Field,"
                  << " ";
        std::cout << "Cal_Len_Index:"
                  << " " << this->field.dest_info.unicast.cal_len_index << ", ";
        std::cout << "DP:"
                  << " " << this->field.dest_info.unicast.dp << ", ";
        std::cout << "TC:"
                  << " " << this->field.dest_info.unicast.tc << ", ";
        std::cout << "Flow ID:"
                  << " " << this->field.dest_info.unicast.flow_id << ". " << endl;
    }
}

void sc_trace(sc_trace_file * tf, const IHeader & v, const std::string & name) {}

FHeader::FHeader() { memset(this->bytes, 0, sizeof(char) * sizeof(this->field)); }

void FHeader::set_bytes(std::string bytes)
{
    if (bytes.size() != sizeof(field))
    {
        throw Exception("error : size is not equal to FTMH.");
    }
    std::copy(bytes.c_str(), bytes.c_str() + bytes.size(), this->bytes);
}

std::string FHeader::get_bytes() { return std::string(this->bytes, sizeof(field)); }

int FHeader::get_size() { return sizeof(field); }

void FHeader::set_type(enum FHeader::Type type) { this->field.type = type; }

FHeader::Type FHeader::get_type() { return this->field.type; }

void FHeader::set_ver(unsigned ver)
{
    if (ver >= 1 << VER_LENGTH)
    {
        throw Exception("error : ver is out of rang.");
    }
    this->field.ver = ver;
}

unsigned FHeader::get_ver() { return this->field.ver; }

void FHeader::set_packet_size(unsigned packet_size)
{
    if (packet_size >= 1 << PACKET_SIZE_LENGTH)
    {
        throw Exception("error : packet_size is out of rang.");
    }
    this->field.packet_size = packet_size;
}

unsigned FHeader::get_packet_size() { return this->field.packet_size; }

void FHeader::set_src_tm_id(unsigned src_tm_id)
{
    if (src_tm_id >= 1 << SRC_TM_ID_LENGTH)
    {
        throw Exception("error : src_tm_id is out of rang.");
    }
    this->field.src_tm_id = src_tm_id;
}

unsigned FHeader::get_src_tm_id() { return this->field.src_tm_id; }

void FHeader::set_multicast_id(unsigned multicast_id)
{

    if (multicast_id >= 1 << MULTICAST_ID_LENGTH)
    {
        throw Exception("error : multicast_id is out of rang.");
    }
    switch (this->field.type)
    {
    case FHeader::TDM_MULTICAST:
        this->field.fabric_dest_info.tdm_multicast.multicast_id = multicast_id;
        break;
    case FHeader::MULTICAST:
        this->field.fabric_dest_info.multicast.multicast_id = multicast_id;
        break;
    default:
        throw Exception("error : Type must be TDM_Multicast/Multicast.");
        break;
    }
}

unsigned FHeader::get_multicast_id()
{
    switch (this->field.type)
    {
    case FHeader::TDM_MULTICAST:
        return this->field.fabric_dest_info.tdm_multicast.multicast_id;
        break;
    case FHeader::MULTICAST:
        return this->field.fabric_dest_info.multicast.multicast_id;
        break;
    default:
        throw Exception("error : Type must be TDM_Multicast/Multicast.");
        break;
    }
}

void FHeader::set_out_port(unsigned out_port)
{
    if (out_port >= 1 << OUT_PORT_LENGTH)
    {
        throw Exception("error : out_port is out of rang.");
    }
    switch (this->field.type)
    {
    case FHeader::TDM_UNICAST:
        this->field.fabric_dest_info.tdm_unicast.out_port = out_port;
        break;
    case FHeader::UNICAST:
        this->field.fabric_dest_info.unicast.out_port = out_port;
        break;
    default:
        throw Exception("error : Type must be TDM_Unicast/Unicast.");
        break;
    }
}

unsigned FHeader::get_out_port()
{
    switch (this->field.type)
    {
    case FHeader::TDM_UNICAST:
        return this->field.fabric_dest_info.tdm_unicast.out_port;
        break;
    case FHeader::UNICAST:
        return this->field.fabric_dest_info.unicast.out_port;
        break;
    default:
        throw Exception("error : Type must be TDM_Unicast/Unicast.");
        break;
    }
}

void FHeader::set_cal_len(unsigned cal_len)
{
    if (cal_len >= 1 << CAL_LEN_LENGTH)
    {
        throw Exception("error : cal_len is out of rang.");
    }
    switch (this->field.type)
    {
    case FHeader::MULTICAST:
        this->field.fabric_dest_info.multicast.cal_len = cal_len;
        break;
    case FHeader::UNICAST:
        this->field.fabric_dest_info.unicast.cal_len = cal_len;
        break;
    default:
        throw Exception("error : Type must be Multicast/Unicast.");
        break;
    }
}

unsigned FHeader::get_cal_len()
{
    switch (this->field.type)
    {
    case FHeader::MULTICAST:
        return this->field.fabric_dest_info.multicast.cal_len;
        break;
    case FHeader::UNICAST:
        return this->field.fabric_dest_info.unicast.cal_len;
        break;
    default:
        throw Exception("error : Type must be Multicast/Unicast.");
        break;
    }
}

void FHeader::set_tc(unsigned tc)
{
    if (tc >= 1 << TC_LENGTH)
    {
        throw Exception("error : tc is out of rang.");
    }
    switch (this->field.type)
    {
    case FHeader::MULTICAST:
        this->field.fabric_dest_info.multicast.tc = tc;
        break;
    case FHeader::UNICAST:
        this->field.fabric_dest_info.unicast.tc = tc;
        break;
    default:
        throw Exception("error : Type must be Multicast/Unicast.");
        break;
    }
}

unsigned FHeader::get_tc()
{
    switch (this->field.type)
    {
    case FHeader::MULTICAST:
        return this->field.fabric_dest_info.multicast.tc;
        break;
    case FHeader::UNICAST:
        return this->field.fabric_dest_info.unicast.tc;
        break;
    default:
        throw Exception("error : Type must be Multicast/Unicast.");
        break;
    }
}

void FHeader::set_dp(unsigned dp)
{
    if (dp >= 1 << DP_LENGTH)
    {
        throw Exception("error : dp is out of rang.");
    }
    switch (this->field.type)
    {
    case FHeader::MULTICAST:
        this->field.fabric_dest_info.multicast.dp = dp;
        break;
    case FHeader::UNICAST:
        this->field.fabric_dest_info.unicast.dp = dp;
        break;
    default:
        throw Exception("error : Type must be Multicast/Unicast.");
        break;
    }
}

unsigned FHeader::get_dp()
{
    switch (this->field.type)
    {
    case FHeader::MULTICAST:
        return this->field.fabric_dest_info.multicast.dp;
        break;
    case FHeader::UNICAST:
        return this->field.fabric_dest_info.unicast.dp;
        break;
    default:
        throw Exception("error : Type must be Multicast/Unicast.");
        break;
    }
}

void FHeader::dump()
{
    std::cout << "FHeader:"
              << " ";
    std::cout << "ver:"
              << " " << this->field.ver << ", ";
    std::cout << "Source TM ID:"
              << " " << this->field.src_tm_id << ", ";
    std::cout << "Packet Size:"
              << " " << this->field.packet_size << ", ";
    if (this->field.type == FHeader::TDM_MULTICAST)
    {
        std::cout << "TDM multicast header,"
                  << " ";
        std::cout << "Fabric dest Info,"
                  << " ";
        std::cout << "Multicast ID:"
                  << " " << this->field.fabric_dest_info.tdm_multicast.multicast_id << "." << endl;
    }
    if (this->field.type == FHeader::TDM_UNICAST)
    {
        std::cout << "TDM unicast header,"
                  << " ";
        std::cout << "Fabric dest Info,"
                  << " ";
        std::cout << "Out port:"
                  << " " << this->field.fabric_dest_info.tdm_unicast.out_port << ". " << endl;
    }
    if (this->field.type == FHeader::MULTICAST)
    {
        std::cout << "Multicast Header,"
                  << " ";
        std::cout << "Fabric dest Info,"
                  << " ";
        std::cout << "Cal len:"
                  << " " << this->field.fabric_dest_info.multicast.cal_len << ", ";
        std::cout << "TC:"
                  << " " << this->field.fabric_dest_info.multicast.tc << ", ";
        std::cout << "DP:"
                  << " " << this->field.fabric_dest_info.multicast.dp << ", ";
        std::cout << "Multicast ID:"
                  << " " << this->field.fabric_dest_info.multicast.multicast_id << ". " << endl;
    }
    if (this->field.type == FHeader::UNICAST)
    {
        std::cout << "Unicast Header,"
                  << " ";
        std::cout << "Fabric dest Info,"
                  << " ";
        std::cout << "Cal len:"
                  << " " << this->field.fabric_dest_info.unicast.cal_len << ", ";
        std::cout << "TC:"
                  << " " << this->field.fabric_dest_info.unicast.tc << ", ";
        std::cout << "DP:"
                  << " " << this->field.fabric_dest_info.unicast.dp << ", ";
        std::cout << "Out port:"
                  << " " << this->field.fabric_dest_info.unicast.out_port << ". " << endl;
    }
}

void sc_trace(sc_trace_file * tf, const FHeader & v, const std::string & name) {}

OHeader::OHeader() { memset(this->bytes, 0, sizeof(char) * sizeof(this->field)); }

void OHeader::set_type(enum OHeader::Type type) { this->field.type = type; }

OHeader::Type OHeader::get_type() { return this->field.type; }

void OHeader::set_channel_no(unsigned channel_no)
{
    if (this->field.type != OHeader::TDM)
    {
        throw Exception("error : Type must be TDM.");
    }
    else if (channel_no >= 1 << CHANNEL_NO_LENGTH)
    {
        throw Exception("error : channel_no is out of rang.");
    }
    else
    {
        this->field.dest_info.tdm.channel_no = channel_no;
    }
}

unsigned OHeader::get_channel_no()
{
    if (this->field.type != OHeader::TDM)
    {
        throw Exception("error : Type must be TDM.");
    }
    return this->field.dest_info.tdm.channel_no;
}

void OHeader::set_src_tm_id(unsigned src_tm_id)
{
    if (src_tm_id >= 1 << SRC_TM_ID_LENGTH)
    {
        throw Exception("error : src_tm_id is out of rang.");
    }
    switch (this->field.type)
    {
    case OHeader::TDM:
        this->field.dest_info.tdm.src_tm_id = src_tm_id;
        break;
    case OHeader::UNICAST:
        this->field.dest_info.unicast.src_tm_id = src_tm_id;
        break;
    default:
        throw Exception("error : Type must be TDM/Unicast.");
        break;
    }
}

unsigned OHeader::get_src_tm_id()
{
    switch (this->field.type)
    {
    case OHeader::MULTICAST:
        return this->field.dest_info.tdm.src_tm_id;
        break;
    case OHeader::UNICAST:
        return this->field.dest_info.unicast.src_tm_id;
        break;
    default:
        throw Exception("error : Type must be TDM/Unicast.");
        break;
    }
}

void OHeader::set_port_no(unsigned port_no)
{
    if (port_no >= 1 << PORT_NO_LENGTH)
    {
        throw Exception("error : port_no is out of rang.");
    }
    switch (this->field.type)
    {
    case OHeader::MULTICAST:
        this->field.dest_info.multicast.port_no = port_no;
        break;
    case OHeader::UNICAST:
        this->field.dest_info.unicast.port_no = port_no;
        break;
    default:
        throw Exception("error : Type must be Multicast/Unicast.");
        break;
    }
}

unsigned OHeader::get_port_no()
{

    switch (this->field.type)
    {
    case OHeader::MULTICAST:
        return this->field.dest_info.multicast.port_no;
        break;
    case OHeader::UNICAST:
        return this->field.dest_info.unicast.port_no;
        break;
    default:
        throw Exception("error : Type must be Multicast/Unicast.");
        break;
    }
}

void OHeader::set_mc_gpi(unsigned mc_gpi)
{
    if (this->field.type != OHeader::MULTICAST)
    {
        throw Exception("error : Type must be Multicast");
    }
    else if (mc_gpi >= 1 << MC_GPI_LENGTH)
    {
        throw Exception("error : mc_gpi is out of rang.");
    }
    else
    {
        this->field.dest_info.multicast.mc_gpi = mc_gpi;
    }
}

unsigned OHeader::get_mc_gpi()
{
    if (this->field.type != OHeader::MULTICAST)
    {
        throw Exception("error : Type must be Multicast");
    }
    else
    {
        return this->field.dest_info.multicast.mc_gpi;
    }
}

int OHeader::get_size() { return sizeof(field); }

void OHeader::dump()
{
    std::cout << "OHeader:"
              << " ";
    if (this->field.type == OHeader::TDM)
    {
        std::cout << "TDM header,"
                  << " ";
        std::cout << "Dest Info,"
                  << " ";
        std::cout << "Channel no:"
                  << " " << this->field.dest_info.tdm.channel_no << ", ";
        std::cout << "Source TM ID:"
                  << " " << this->field.dest_info.tdm.src_tm_id << "." << endl;
    }
    if (this->field.type == OHeader::MULTICAST)
    {
        std::cout << "Multicast Header,"
                  << " ";
        std::cout << "Dest Info,"
                  << " ";
        std::cout << "Port no:"
                  << " " << this->field.dest_info.multicast.port_no << ", ";
        std::cout << "Multicast gpi ID:"
                  << " " << this->field.dest_info.multicast.mc_gpi << ". " << endl;
    }
    if (this->field.type == FHeader::UNICAST)
    {
        std::cout << "Unicast Header,"
                  << " ";
        std::cout << "Dest Info,"
                  << " ";
        std::cout << "Port no:"
                  << " " << this->field.dest_info.unicast.port_no << ", ";
        std::cout << "Source TM ID:"
                  << " " << this->field.dest_info.unicast.src_tm_id << ". " << endl;
    }
}

std::string OHeader::get_bytes() { return std::string(this->bytes, sizeof(field)); }

void OHeader::set_bytes(std::string bytes)
{
    if (bytes.size() != sizeof(field))
    {
        throw Exception("error : size is not equal to OTMH.");
    }
    std::copy(bytes.c_str(), bytes.c_str() + bytes.size(), this->bytes);
}

#undef ITMH_TYPE_LENGTH
#undef CHANNEL_NO_LENGTH
#undef TC_LENGTH
#undef DP_LENGTH
#undef MULTICAST_ID_LENGTH
#undef CAL_LEN_INDEX_LENGTH
#undef FLOW_ID_LENGTH

#undef FTMH_TYPE_LENGTH
#undef VER_LENGTH
#undef PACKET_SIZE_LENGTH
#undef SRC_TM_ID_LENGTH
#undef OUT_PORT_LENGTH
#undef CAL_LEN_LENGTH

#undef OTMH_TYPE_LENGTH
#undef PORT_NO_LENGTH
#undef MC_GPI_LENGTH