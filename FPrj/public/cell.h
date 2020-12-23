#ifndef _CELL_H_
#define _CELL_H_
#ifndef SC_USE_STD_STRING
#define SC_USE_STD_STRING
#endif
#include "systemc.h"
#include <iomanip>
#include <iostream>
#if __cplusplus > 199711L
#include <type_traits>
#endif
#include "crc.h"

#define CELL_SIZE (sizeof(cell))
#define CELL_UNICAST_SIZE (sizeof(cell_unicast))
#define CELL_FLOWSTS_SIZE (sizeof(cell_flowsts))
#define CELL_CREDIT_SIZE (sizeof(cell_credit))
//#define CELL_ROUTE_SIZE (sizeof(cell_route))
//#define CELL_SYNC_SIZE (sizeof(cell_sync))
#define RAW_SIZE 276
#define CELL_DATA_SIZE 256
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
#ifdef __GNUC__

#define GNUC_PACKED __attribute__((packed))

#else

#define GNUC_PACKED

#endif

#ifdef WIN32

#pragma pack(1)

#endif

#if __cplusplus >= 201703L
#ifndef GET_UBIT_FIELD_WIDTH
#define GET_UBIT_FIELD_WIDTH(T, f)                                                                                     \
    []() constexpr->unsigned int                                                                                       \
    {                                                                                                                  \
        T t{};                                                                                                         \
        t.f = ~0;                                                                                                      \
        unsigned int bitCount = 0;                                                                                     \
        while (t.f != 0)                                                                                               \
        {                                                                                                              \
            t.f &= (t.f - 1); /*t.f >>= 1;*/                                                                           \
            ++bitCount;                                                                                                \
        }                                                                                                              \
        return bitCount;                                                                                               \
    }                                                                                                                  \
    ()
#endif

#ifndef GET_UBIT_FIELD_MAX
#define GET_UBIT_FIELD_MAX(T, f)                                                                                       \
    []() constexpr->unsigned int                                                                                       \
    {                                                                                                                  \
        T t{};                                                                                                         \
        t.f = ~0;                                                                                                      \
        return t.f;                                                                                                    \
    }                                                                                                                  \
    ()
#endif
#else
#endif

struct cell_unicast;
struct cell_flowsts;
struct cell_credit;
// struct cell_route;
// struct cell_sync;

typedef cell_unicast cell;
struct cell_unicast
{
    union
    {
        char raw_data[]; // RAW_SIZE];
        struct
        {
            unsigned ver : 2;
            unsigned type : 4;
            unsigned lv : 1;
            unsigned fsyn : 1;
            unsigned ssyn : 1;
            unsigned up : 1;
            unsigned mp : 1;
            unsigned tp : 1;
            unsigned cp : 1;
            unsigned eop : 1;
            unsigned pack : 1;
            unsigned tsci : 3;
            unsigned st : 1;
            unsigned uci : 2;
            unsigned mci : 2;
            unsigned len : 9;
            unsigned src : 11;
            unsigned /*reserved*/ : 9;
            unsigned dest : 12;
            unsigned /*reserved*/ : 2;
            unsigned fseq : 6;
            unsigned fts : 24;
            unsigned /*reserved*/ : 2;
            unsigned sseq : 6;
            unsigned sts : 24;
            char data[CELL_DATA_SIZE];
            unsigned crc;
        } GNUC_PACKED;
    };
    inline unsigned cell_type() const { return type; }
    inline void cell_type(unsigned t) { type = t; }

    inline unsigned source_id() const { return src; }
    inline void source_id(unsigned t) { src = t; }

    inline unsigned dest_id() const { return dest; }
    inline void dest_id(unsigned t) { dest = t; }

    inline unsigned cell_id() const { return fseq; }
    inline void cell_id(unsigned t) { fseq = t; }

    inline unsigned packet_id() const { return fts; }
    inline void packet_id(unsigned t) { fts = t; }

    inline unsigned timeslot() const { return fts; }
    inline void timeslot(unsigned t) { fts = t; }

    void dump(std::ostream & os = std::cout)
    {
        // os << "packet id: " << packet_id() << " cell id: " << cell_id();
        dump_header(os);
        os << " \" ";
        for (int i = 0; i < sizeof(*this); i++)
        {
            os << std::hex << (0xFF & raw_data[i]) << " ";
        }
        os << " \"" << std::endl;
    }
    /*void dump_header()
    {
        std::cout<<std::boolalpha<<std::setw(20)<<setiosflags(ios::left)<<" packet id(timeslot): "<<packet_id()<<"\tcell
    id(sequence): "<<cell_id()<<"\ttype"<<type<<"\tlength"<<len<<" eop "<<eop<<std::endl;
    }*/
    void dump_header(std::ostream & os = std::cout)
    {
        os << std::boolalpha << std::setw(15) << setiosflags(ios::left) << " packet id(timeslot): " << packet_id()
           << "\tcell id(sequence): " << cell_id() << "\ttype" << type << "\tlength" << len << " eop " << eop
           << std::endl;
    }

    void dump_header(const std::string & s, std::ostream & os = std::cout) { dump_header(s.c_str(), os); }

    void dump_header(const char * s, std::ostream & os = std::cout)
    {
        os << std::boolalpha << std::setw(15) << setiosflags(ios::left) << s << " packet id(timeslot): " << packet_id()
           << "\tcell id(sequence): " << cell_id() << "\ttype" << type << "\tlength" << len << "\teop " << eop
           << "\tsource: " << source_id() << "\tdest: " << dest_id() << std::endl;
    }

    unsigned refresh_crc()
    {
        crc = crc16_CCITT((unsigned char *)raw_data, sizeof(*this) - sizeof(crc));
        // cout<<crc<<endl;
        // dump_header("crc refersh");
        return crc;
    }

    bool verify_crc()
    {
        unsigned current_crc = crc16_CCITT((unsigned char *)raw_data, sizeof(*this) - sizeof(crc));
        // cout<<current_crc<<" "<<crc<<endl;
        // dump_header("crc verify");
        return current_crc == crc;
    }

    bool is_empty() { return (type == CellType::Empty); }

    void set_empty() { type = CellType::Empty; }

    cell_unicast() =
        default; // class without a user-provided or deleted default constructor is zero-initialized since 201103L
    /*cell_unicast() //:raw_data({0})
    {
#if __cplusplus > 199711L
        static_assert(std::is_trivially_copyable<cell_unicast>::value && std::is_standard_layout<cell_unicast>::value,
"Error: cell must be TriviallyCopyable with StandardLayout"); #endif std::memset(raw_data, 0, CELL_SIZE);
    }*/
    /*cell_unicast(cell_flowsts& c)
    {
        std::copy(c.raw_data, c.raw_data+sizeof(c), raw_data);
    }
    cell_unicast(cell_credit& c)
    {
        std::copy(c.raw_data, c.raw_data+sizeof(c), raw_data);
    }*/
    template <typename T> cell_unicast(T & c) { std::copy(c.raw_data, c.raw_data + sizeof(c), raw_data); }

    /*void extract(cell_flowsts& c)
    {
        std::copy(raw_data, raw_data+sizeof(c), c.raw_data);
    }
    void extract(cell_credit& c)
    {
        std::copy(raw_data, raw_data+sizeof(c), c.raw_data);
    }*/
    template <typename T> void extract(T & c) { std::copy(raw_data, raw_data + sizeof(c), c.raw_data); }
    bool operator==(const cell_unicast & c) const
    {
        return std::equal(this->raw_data, this->raw_data + CELL_SIZE, c.raw_data);
    }
    friend std::ostream & operator<<(std::ostream & os, const cell_unicast & t) { return os << ""; }
    bool operator<(const cell_unicast & c) const
    {
        return this->packet_id() == c.packet_id()
                   ? (this->cell_id() == c.cell_id() ? (this->source_id() < c.source_id())
                                                     : (this->cell_id() < c.cell_id()))
                   : (this->packet_id() < c.packet_id());
    }
    bool operator>(const cell_unicast & c) const
    {
        return this->packet_id() == c.packet_id()
                   ? (this->cell_id() == c.cell_id() ? (this->source_id() > c.source_id())
                                                     : (this->cell_id() > c.cell_id()))
                   : (this->packet_id() > c.packet_id());
    }
};

#define CELL_FLOWSTS_REQSEQ_SIZE 11
struct cell_flowsts
{
    union
    {
        char raw_data[]; // RAW_SIZE];
        struct
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
            unsigned reqseq : CELL_FLOWSTS_REQSEQ_SIZE;
            unsigned crc;
        } GNUC_PACKED;
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

    inline unsigned request_id() const { return reqseq; }
    inline void request_id(unsigned t) { reqseq = t; }

    void dump(std::ostream & os = std::cout)
    {
        os << "destination: " << dest_id() << " flow: " << flow_id();
        os << " \" ";
        for (int i = 0; i < CELL_FLOWSTS_SIZE; i++)
        {
            os << std::hex << (0xFF & raw_data[i]) << " ";
        }
        os << " \"" << std::endl;
    }

    void dump_header(std::ostream & os = std::cout)
    {
        os << std::boolalpha << std::setw(15) << setiosflags(ios::left) << " flow status destination: " << dest_id()
           << "\tflow: " << flow_id() << "\ttype" << type << std::endl;
    }

    void dump_header(const std::string & s, std::ostream & os = std::cout) { dump_header(s.c_str(), os); }

    void dump_header(const char * s, std::ostream & os = std::cout)
    {
        os << std::boolalpha << std::setw(15) << setiosflags(ios::left) << s
           << " flow status destination: " << dest_id() << "\tflow: " << flow_id() << "\ttype" << type << std::endl;
    }

    unsigned refresh_crc()
    {
        crc = crc16_CCITT((unsigned char *)raw_data, sizeof(*this) - sizeof(crc));
        // cout<<crc<<endl;
        // dump_header("crc refersh");
        return crc;
    }

    bool verify_crc()
    {
        unsigned current_crc = crc16_CCITT((unsigned char *)raw_data, sizeof(*this) - sizeof(crc));
        // cout<<current_crc<<" "<<crc<<endl;
        // dump_header("crc verify");
        return current_crc == crc;
    }

    bool is_empty() { return (type == CellType::Empty); }

    void set_empty() { type = CellType::Empty; }

    cell_flowsts() = default;
    /*cell_flowsts() //:raw_data({0})
    {
#if __cplusplus > 199711L
        static_assert(std::is_trivially_copyable<cell_flowsts>::value && std::is_standard_layout<cell_flowsts>::value,
"Error: cell_flowsts must be TriviallyCopyable with StandardLayout"); #endif std::memset(raw_data, 0,
CELL_FLOWSTS_SIZE);
    }*/
    bool operator==(const cell_flowsts & c) const
    {
        return std::equal(this->raw_data, this->raw_data + sizeof(*this), c.raw_data);
    }
    friend std::ostream & operator<<(std::ostream & os, const cell_flowsts & t) { return os << ""; }
    bool operator<(const cell_flowsts & c) const { return this->request() < c.request(); }
    bool operator>(const cell_flowsts & c) const { return this->request() > c.request(); }
};

struct cell_credit
{
    union
    {
        char raw_data[]; // RAW_SIZE];
        struct
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
            unsigned /*reserved*/ : 13;
            unsigned crc;
        } GNUC_PACKED;
    };
    inline unsigned source_type() const { return srctype; }
    inline void source_type(unsigned t) { srctype = t; }

    inline unsigned source_id() const { return src; }
    inline void source_id(unsigned t) { src = t; }

    inline unsigned dest_id() const { return dest; }
    inline void dest_id(unsigned t) { dest = t; }

    inline unsigned flow_id() const { return qid; }
    inline void flow_id(unsigned t) { qid = t; }

    void dump(std::ostream & os = std::cout)
    {
        os << "destination: " << dest_id() << " flow: " << flow_id();
        os << " \" ";
        for (int i = 0; i < CELL_CREDIT_SIZE; i++)
        {
            os << std::hex << (0xFF & raw_data[i]) << " ";
        }
        os << " \"" << std::endl;
    }

    void dump_header(std::ostream & os = std::cout)
    {
        os << std::boolalpha << std::setw(15) << setiosflags(ios::left) << " credit grant destination: " << dest_id()
           << "\tflow: " << flow_id() << "\ttype" << type << std::endl;
    }

    void dump_header(const std::string & s, std::ostream & os = std::cout) { dump_header(s.c_str(), os); }

    void dump_header(const char * s, std::ostream & os = std::cout)
    {
        os << std::boolalpha << std::setw(15) << setiosflags(ios::left) << s
           << " credit grant destination: " << dest_id() << "\tflow: " << flow_id() << "\ttype" << type << std::endl;
    }

    unsigned refresh_crc()
    {
        crc = crc16_CCITT((unsigned char *)raw_data, sizeof(*this) - sizeof(crc));
        // cout<<crc<<endl;
        // dump_header("crc refersh");
        return crc;
    }

    bool verify_crc()
    {
        unsigned current_crc = crc16_CCITT((unsigned char *)raw_data, sizeof(*this) - sizeof(crc));
        // cout<<current_crc<<" "<<crc<<endl;
        // dump_header("crc verify");
        return current_crc == crc;
    }

    bool is_empty() { return (type == CellType::Empty); }

    void set_empty() { type = CellType::Empty; }

    cell_credit() = default;
    /*cell_credit() //:raw_data({0})
    {
#if __cplusplus > 199711L
        static_assert(std::is_trivially_copyable<cell_credit>::value && std::is_standard_layout<cell_credit>::value,
"Error: cell_credit must be TriviallyCopyable with StandardLayout"); #endif std::memset(raw_data, 0, CELL_CREDIT_SIZE);
    }*/
    bool operator==(const cell_credit & c) const
    {
        return std::equal(this->raw_data, this->raw_data + sizeof(*this), c.raw_data);
    }
    friend std::ostream & operator<<(std::ostream & os, const cell_credit & t) { return os << ""; }
    bool operator<(const cell_credit & c) const { return this->type < c.type; /*dumb*/ }
    bool operator>(const cell_credit & c) const { return this->type > c.type; /*dumb*/ }
};

extern void sc_trace(sc_trace_file * tf, const cell & v, const sc_string & name);

#undef GNUC_PACKED
#endif //_CELL_H_
