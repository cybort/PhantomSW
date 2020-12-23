/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              prv_deftype.h
   Project Code: F-Switch
   Module Name : Cell format defination
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : cell 格式定义

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef _SWITCH_CELL_H_
#define _SWITCH_CELL_H_


#define CELL_FORMAT_SIZE    276     /* total size of cell paket */
#define CELL_DATA_SIZE      256     /* paylaod size of cell paket */

#define CELL_FORMAT_VERSION_SIZE            2
#define CELL_FORMAT_TYPE_SIZE               4
#define CELL_FORMAT_LINK_VALID_SIZE         1
#define CELL_FORMAT_FSYN_FLAG_SIZE          1
#define CELL_FORMAT_SSYN_FLAG_SIZE          1
#define CELL_FORMAT_UNICAST_PAUSE_FLAG_SIZE      1
#define CELL_FORMAT_MULTCAST_PAUSE_FLAG_SIZE     1
#define CELL_FORMAT_TDM_PAUSE_FLAG_SIZE      1
#define CELL_FORMAT_CONTROL_PAUSE_FLAG_SIZE      1
#define CELL_FORMAT_LAST_FLAG_SIZE          1
#define CELL_FORMAT_PAKTED_FLAG_SIZE        1
#define CELL_FORMAT_TIMESLOT_CONGEST_SIZE   3
#define CELL_FORMAT_SUB_TIMESLOT_TYPE_SIZE  1
#define CELL_FORMAT_UNICAST_CONGEST_SIZE    2
#define CELL_FORMAT_MULTCAST_CONGEST_SIZE   2
#define CELL_FORMAT_PAYLAOD_LEN_SIZE        9
#define CELL_FORMAT_SOURCE_ID_SIZE          11
#define CELL_FORMAT_RESERVED1_SIZE          9
#define CELL_FORMAT_DEST_ID_SIZE            12;
#define CELL_FORMAT_RESEVERED2_SIZE         2
#define CELL_FORMAT_PRIMARY_SEQ_SIZE        6
#define CELL_FORMAT_PRIMARY_TIMESLOT_SIZE   24
#define CELL_FORMAT_SUB_SEQ_SIZE            6
#define CELL_FORMAT_SUB_TIMESLOT_SIZE       24

#define CELL_SIZE           (sizeof(CELL))
#define CELL_FLOWSTS_SIZE   (sizeof(cell_flowsts))
#define CELL_CREDIT_SIZE    (sizeof(cell_credit))
#define CELL_ROUTE_SIZE     (sizeof(cell_route))



namespace CellType
{
enum cellType
{
    Unicast,
    Multicast,
    Empty, 
    FlowSts = 8,
    Credit,
    Route,
    Sync
};
}

namespace SourceType
{
enum sourceType
{
    FTM = 0,
    FS1,
    FS2, 
    FS3
};
}


/*用于System的模板，需要重载==，<<等运算符*/
struct CELL
{
    union
    {
        char  raw_data[CELL_FORMAT_SIZE];
        struct __attribute__ ((packed))
        {
            unsigned version    :   CELL_FORMAT_VERSION_SIZE; /* Version of cell */
            unsigned type       :   CELL_FORMAT_TYPE_SIZE;    /* type of cell */
            unsigned link_valid :   CELL_FORMAT_LINK_VALID_SIZE; /* indicate link status */
            unsigned fsyn       :   CELL_FORMAT_FSYN_FLAG_SIZE; /* primary timeslot complete flag */
            unsigned ssyn       :   CELL_FORMAT_SSYN_FLAG_SIZE; /* subsidiary timeslot complete flag */ 
            unsigned up         :   CELL_FORMAT_UNICAST_PAUSE_FLAG_SIZE; /* unicast flow Control flag */
            unsigned mp         :   CELL_FORMAT_MULTCAST_PAUSE_FLAG_SIZE; /* multicast flow control flag */
            unsigned tp         :   CELL_FORMAT_TDM_PAUSE_FLAG_SIZE; /* tdm flow control flag */ 
            unsigned cp         :   CELL_FORMAT_CONTROL_PAUSE_FLAG_SIZE;
            unsigned eop        :   CELL_FORMAT_PAKTED_FLAG_SIZE;  /* indicate current cell is the last cell of packet */
            unsigned pack       :   CELL_FORMAT_PAKTED_FLAG_SIZE; /* indicate current cell is a packed cell */
            unsigned tsci       :   CELL_FORMAT_TIMESLOT_CONGEST_SIZE; /* indicate timeslot congest */
            unsigned st         :   CELL_FORMAT_SUB_TIMESLOT_TYPE_SIZE; /* subsidiary timeslot type */
            unsigned uci        :   CELL_FORMAT_UNICAST_CONGEST_SIZE;   /* indicate unicast congest */
            unsigned mci        :   CELL_FORMAT_MULTCAST_CONGEST_SIZE; /* indicate multicast congest */
            unsigned len        :   CELL_FORMAT_PAYLAOD_LEN_SIZE; /* cell paylaod len */ 
            unsigned source_id  :   CELL_FORMAT_SOURCE_ID_SIZE; /* source id  */
            unsigned            :   CELL_FORMAT_RESERVED1_SIZE; /* reserved */
            unsigned dest_id    :   CELL_FORMAT_DEST_ID_SIZE; /* destination id */
            unsigned            :   CELL_FORMAT_RESEVERED2_SIZE; /* reserved */
            unsigned fseq       :   CELL_FORMAT_PRIMARY_SEQ_SIZE; /* primary sequnce NO. */
            unsigned fts        :   CELL_FORMAT_PRIMARY_TIMESLOT_SIZE; /* primary timeslot id */
            unsigned            :   CELL_FORMAT_RESEVERED2_SIZE; /* reserved */ 
            unsigned sseq       :   CELL_FORMAT_SUB_SEQ_SIZE; /* subsidiary sequence NO. */
            unsigned sts        :   CELL_FORMAT_SUB_TIMESLOT_SIZE; /* subsidiary timeslot id */
            char data[CELL_DATA_SIZE]; /* paylaod data */
            unsigned crc:17;
        };
    };

    CELL(){}
    
    template <typename T>
    void extract(T& c)
    {
        std::copy(raw_data, raw_data+sizeof(c), c.raw_data);
    }

    inline bool operator == (const CELL & rhs) const
    {
        return std::equal(this->raw_data, this->raw_data+CELL_FORMAT_SIZE, rhs.raw_data);
    }
    bool operator<(const CELL &c) const
    {
        return this->fts == c.fts
                   ? (this->fseq == c.fseq ? (this->source_id < c.source_id) : (this->fseq < c.fseq))
                   : (this->fts < c.fts);
    }
    bool operator>(const CELL &c) const
    {
        return this->fts == c.fts
                   ? (this->fseq == c.fseq ? (this->source_id > c.source_id) : (this->fseq > c.fseq))
                   : (this->fts > c.fts);
    }
};

inline ostream& operator << ( ostream& os, const CELL & a )
{
    os << "streaming of struct pkt not implemented";
    return os;
}

struct cell_flowsts
{
    union
    {
        char raw_data[]; // RAW_SIZE];
        struct __attribute__ ((packed))
        {
            unsigned ver : 2;
            unsigned type : 4;
            unsigned lv : 1;
            unsigned up : 1;
            unsigned mp : 1;
            unsigned tp : 1;
            unsigned cp : 1;
            unsigned tsci : 3;
            unsigned srctype : 6;
            unsigned /*reserved*/ : 1;
            unsigned src : 11;
            unsigned dest : 11;
            unsigned /*reserved*/ : 2;
            unsigned fid : 19;
            unsigned req : 2;
            unsigned /*reserved*/ : 11;
            unsigned crc : 19;
        };
    };
    
    inline unsigned source_type() const { return srctype; }
    inline void source_type(unsigned t) { srctype = t; }
    
    inline unsigned source_id() const { return src; }
    inline void source_id(unsigned t) { src = t; }

    inline unsigned dest_id() const { return dest; }
    inline void dest_id(unsigned t) { dest = t; }

    inline unsigned flow_id() const { return fid; }
    inline void flow_id(unsigned t) { fid = t; }
    
    inline unsigned request() const { return req; }
    inline void request(unsigned t) { req = t; }
    
    cell_flowsts(){}
    inline bool operator == (const cell_flowsts & rhs) const
    {
        return std::equal(this->raw_data, this->raw_data+CELL_FLOWSTS_SIZE, rhs.raw_data);
    }
};

struct cell_credit
{
    union
    {
        char raw_data[]; // RAW_SIZE];
        struct __attribute__ ((packed))
        {
            unsigned ver : 2;
            unsigned type : 4;
            unsigned lv : 1;
            unsigned up : 1;
            unsigned mp : 1;
            unsigned tp : 1;
            unsigned cp : 1;
            unsigned tsci : 3;
            unsigned srctype : 6;
            unsigned /*reserved*/ : 1;
            unsigned src : 11;
            unsigned dest : 11;
            unsigned /*reserved*/ : 2;
            unsigned qid : 19;
            unsigned reqseq : 13;
            unsigned crc : 19;
        } ;
    };
    
    inline unsigned source_type() const { return srctype; }
    inline void source_type(unsigned t) { srctype = t; }
    
    inline unsigned source_id() const { return src; }
    inline void source_id(unsigned t) { src = t; }

    inline unsigned dest_id() const { return dest; }
    inline void dest_id(unsigned t) { dest = t; }

    inline unsigned flow_id() const { return qid; }
    inline void flow_id(unsigned t) { qid = t; }

    cell_credit(){}
    inline bool operator == (const cell_credit & rhs) const
    {
        return std::equal(this->raw_data, this->raw_data+CELL_CREDIT_SIZE, rhs.raw_data);
    }
};


struct cell_route
{
    union
    {
        char raw_data[]; // RAW_SIZE];
        struct __attribute__ ((packed))
        {
            unsigned ver : 2;
            unsigned type : 4;
            unsigned lv : 1;
            unsigned up : 1;
            unsigned mp : 1;
            unsigned tp : 1;
            unsigned cp : 1;
            unsigned tsci : 3;
            unsigned /*reserved*/ : 2;
            unsigned rc : 1;
            unsigned srclvl : 3;
            unsigned /*reserved*/ : 1;
            unsigned src : 11;
            unsigned dest : 11;
            unsigned /*reserved*/ : 3;
            unsigned rack : 6;
            unsigned /*reserved*/ : 2;
            unsigned srclink : 10;
            unsigned /*reserved*/ : 13;
            unsigned crc : 19;
        } ;
    };
    
    inline unsigned route_connect() const { return rc; }
    inline void route_connect(unsigned t) { rc = t; }

    inline unsigned source_type() const { return srclvl; }
    inline void source_type(unsigned t) { srclvl = t; }

    inline unsigned source_id() const { return src; }
    inline void source_id(unsigned t) { src = t; }
    
    inline unsigned dest_id() const { return dest; }/*表示能够到达的*/
    inline void dest_id(unsigned t) { dest = t; }

    inline unsigned source_link() const { return srclink; }
    inline void source_link(unsigned t) { dest = t; }

    cell_route(){}
    inline bool operator == (const cell_route & rhs) const
    {
        return std::equal(this->raw_data, this->raw_data+CELL_CREDIT_SIZE, rhs.raw_data);
    }
};


inline void
#if defined(SC_API_VERSION_STRING)
sc_trace( sc_trace_file* tf, const CELL& a, const std::string& name )
#else
sc_trace( sc_trace_file* tf, const CELL& a, const sc_string& name )
#endif
{
  sc_trace( tf, a.link_valid, name + ".link_valid" );
  sc_trace( tf, a.fsyn, name + ".fsyn" );
  sc_trace( tf, a.ssyn, name + ".ssyn" );
}

#endif

