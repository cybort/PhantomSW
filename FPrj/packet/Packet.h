/*
 * @Author: your name
 * @Date: 2020-11-02 16:06:15
 * @LastEditTime: 2021-01-12 10:21:46
 * @LastEditors: Zhao Yunpeng
 * @Description: In User Settings Edit
 * @FilePath: \FPrj\packet\packet.h
 */
#ifndef _PACKET_H_
#define _PACKET_H_

#include "Exception.h"
#include "Header.h"
#include "systemc.h"

#define PACKET_PAYLOAD_MAX_SIZE 1024 * 128
class Packet
{
private:
    void virtual fieldToBytes() = 0;

    void virtual bytesToField() = 0;

public:
    void virtual set_payload(std::string payload) = 0;

    std::string virtual get_payload() = 0;

    void virtual set_bytes(std::string bytes) = 0;

    std::string virtual get_bytes() = 0;

    void virtual dump() = 0;
};

class IPacket : Packet
{
private:
    struct
    {
        IHeader itmh;

        std::string payload;
    } field;

    std::string bytes;

    void fieldToBytes();

    void bytesToField();

public:
    void set_itmh(IHeader itmh);

    IHeader get_itmh();

    void set_payload(std::string payload);

    std::string get_payload();

    void set_bytes(std::string bytes);

    std::string get_bytes();

    void dump();
};

extern void sc_trace(sc_trace_file * tf, const IPacket & v, const std::string & name);

class FPacket : Packet
{
private:
    struct
    {
        FHeader ftmh;

        std::string payload;
    } field;

    std::string bytes;

    void fieldToBytes();

    void bytesToField();

public:
    void set_ftmh(FHeader ftmh);

    FHeader get_ftmh();

    void set_payload(std::string payload);

    std::string get_payload();

    void set_bytes(std::string bytes);

    std::string get_bytes();

    void dump();
};

extern void sc_trace(sc_trace_file * tf, const FPacket & v, const std::string & name);

class OPacket : Packet
{
private:
    struct
    {
        OHeader otmh;

        std::string payload;
    } field;

    std::string bytes;

    void fieldToBytes();

    void bytesToField();

public:
    void set_otmh(OHeader otmh);

    OHeader get_otmh();

    void set_payload(std::string payload);

    std::string get_payload();

    void set_bytes(std::string bytes);

    std::string get_bytes();

    void dump();
};

extern void sc_trace(sc_trace_file * tf, const FPacket & v, const std::string & name);

#endif