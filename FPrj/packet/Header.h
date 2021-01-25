#ifndef _HEADER_H_
#define _HEADER_H_

#include "Exception.h"
#include "config.h"
#include "systemc.h"

#ifdef __GNUC__
#define GNUC_PACKED __attribute__((packed))
#else
#define GNUC_PACKED
#endif

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

class Header
{

    virtual std::string get_bytes() = 0;

    virtual void set_bytes(std::string bytes) = 0;

    virtual int get_size() = 0;

    virtual void dump() = 0;
};

class IHeader : Header
{
public:
    enum Type
    {
        EMPTY,
        TDM,
        MULTICAST,
        UNICAST
    };

    IHeader();

    void set_type(enum Type type);

    Type get_type();

    void set_channel_no(unsigned channel_no);

    unsigned get_channel_no();

    void set_tc(unsigned tc);

    unsigned get_tc();

    void set_dp(unsigned dp);

    unsigned get_dp();

    void set_multicast_id(unsigned multicast_id);

    unsigned get_multicast_id();

    void set_cal_len_index(unsigned cal_len_index);

    unsigned get_cal_len_index();

    void set_flow_id(unsigned flow_id);

    unsigned get_flow_id();

    void set_bytes(std::string bytes);

    std::string get_bytes();

    int get_size();

    void dump();

    bool operator==(const IHeader & rhs) const
    {
        return (std::equal(this->bytes, this->bytes + sizeof(field), rhs.bytes));
    }

private:
    union
    {
        struct
        {
            Type type : ITMH_TYPE_LENGTH;
            union
            {
                struct
                {
                    unsigned /*reserved*/ : 20;
                    unsigned channel_no : CHANNEL_NO_LENGTH;
                } GNUC_PACKED tdm;

                struct
                {
                    unsigned tc : TC_LENGTH;
                    unsigned dp : DP_LENGTH;
                    unsigned /*reserved*/ : 6;
                    unsigned multicast_id : MULTICAST_ID_LENGTH;
                } GNUC_PACKED multicast;

                struct
                {
                    unsigned tc : TC_LENGTH;
                    unsigned dp : DP_LENGTH;
                    unsigned cal_len_index : CAL_LEN_INDEX_LENGTH;
                    unsigned /*reserved*/ : 2;
                    unsigned flow_id : FLOW_ID_LENGTH;
                } GNUC_PACKED unicast;

            } dest_info;

        } GNUC_PACKED field;

        char bytes[sizeof(field)];
    };
};

extern void sc_trace(sc_trace_file * tf, const IHeader & v, const std::string & name);

class FHeader : Header
{
public:
    enum Type
    {
        TDM_MULTICAST,
        TDM_UNICAST,
        MULTICAST,
        UNICAST
    };

    FHeader();

    std::string get_bytes();

    void set_bytes(std::string bytes);

    int get_size();

    void set_type(enum Type type);

    Type get_type();

    void set_ver(unsigned ver);

    unsigned get_ver();

    void set_packet_size(unsigned packet_size);

    unsigned get_packet_size();

    void set_src_tm_id(unsigned src_tm_id);

    unsigned get_src_tm_id();

    void set_multicast_id(unsigned multicast_id);

    unsigned get_multicast_id();

    void set_out_port(unsigned out_port);

    unsigned get_out_port();

    void set_cal_len(unsigned cal_len);

    unsigned get_cal_len();

    void set_tc(unsigned tc);

    unsigned get_tc();

    void set_dp(unsigned dp);

    unsigned get_dp();

    void dump();

    bool operator==(const FHeader & rhs) const
    {
        return (std::equal(this->bytes, this->bytes + sizeof(field), rhs.bytes));
    }

private:
    union
    {
        struct
        {
            Type type : FTMH_TYPE_LENGTH;
            unsigned ver : VER_LENGTH;
            unsigned packet_size : PACKET_SIZE_LENGTH;
            unsigned /*reserved*/ : 1;
            unsigned src_tm_id : SRC_TM_ID_LENGTH;
            union
            {

                struct
                {
                    unsigned rsv : 16;
                    unsigned multicast_id : MULTICAST_ID_LENGTH;
                } GNUC_PACKED tdm_multicast;

                struct
                {
                    unsigned rsv : 24;
                    unsigned out_port : OUT_PORT_LENGTH;
                } GNUC_PACKED tdm_unicast;

                struct
                {
                    unsigned rsv : 1;
                    unsigned cal_len : CAL_LEN_LENGTH;
                    unsigned tc : TC_LENGTH;
                    unsigned dp : DP_LENGTH;
                    unsigned multicast_id : MULTICAST_ID_LENGTH;
                } GNUC_PACKED multicast;

                struct
                {
                    unsigned /*reserved*/ : 1;
                    unsigned cal_len : CAL_LEN_LENGTH;
                    unsigned tc : TC_LENGTH;
                    unsigned dp : DP_LENGTH;
                    unsigned rsv : 9;
                    unsigned out_port : OUT_PORT_LENGTH;
                } GNUC_PACKED unicast;

            } fabric_dest_info;

        } GNUC_PACKED field;

        char bytes[sizeof(field)];
    };
};

extern void sc_trace(sc_trace_file * tf, const FHeader & v, const std::string & name);

class OHeader : Header
{
public:
    enum Type
    {
        TDM = 1,
        MULTICAST,
        UNICAST
    };

    OHeader();

    std::string get_bytes();

    void set_bytes(std::string bytes);

    void set_type(enum Type type);

    Type get_type();

    void set_channel_no(unsigned channel_no);

    unsigned get_channel_no();

    void set_src_tm_id(unsigned src_tm_id);

    unsigned get_src_tm_id();

    void set_port_no(unsigned port_no);

    unsigned get_port_no();

    void set_mc_gpi(unsigned mc_gpi);

    unsigned get_mc_gpi();

    int get_size();

    void dump();

    bool operator==(const OHeader & rhs) const
    {
        return (std::equal(this->bytes, this->bytes + sizeof(field), rhs.bytes));
    }

private:
    union
    {
        struct
        {
            Type type : OTMH_TYPE_LENGTH;
            union
            {

                struct
                {
                    unsigned channel_no : CHANNEL_NO_LENGTH;
                    unsigned /*reserved*/ : 9;
                    unsigned src_tm_id : SRC_TM_ID_LENGTH;
                } GNUC_PACKED tdm;

                struct
                {
                    unsigned port_no : PORT_NO_LENGTH;
                    unsigned mc_gpi : MC_GPI_LENGTH;
                } GNUC_PACKED multicast;

                struct
                {
                    unsigned port_no : PORT_NO_LENGTH;
                    unsigned /*reserved*/ : 11;
                    unsigned src_tm_id : SRC_TM_ID_LENGTH;
                } GNUC_PACKED unicast;

            } dest_info;

        } GNUC_PACKED field;

        char bytes[sizeof(field)];
    };
};

extern void sc_trace(sc_trace_file * tf, const OHeader & v, const std::string & name);

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

#undef GNUC_PACKED

#endif