#include "Packet.h"

void IPacket::fieldToBytes()
{
    std::string headerBytes;
    try
    {
        headerBytes = this->field.itmh.get_bytes();
        this->bytes = headerBytes.append(this->field.payload);
    }
    catch (Exception & e)
    {
        throw(e);
    }
}

void IPacket::bytesToField()
{
    int header_size = this->field.itmh.get_size();
    if (this->bytes.size() <= 0)
    {
        throw Exception("error : bytes size must lager than 0.");
    }
    std::string header_bytes = this->bytes.substr(0, header_size);
    std::string payload_bytes = this->bytes.substr(header_size, this->bytes.size() - header_size);
    this->field.payload = payload_bytes;
    try
    {
        this->field.itmh.set_bytes(header_bytes);
    }
    catch (Exception & e)
    {
        throw(e);
    }
}

void IPacket::set_itmh(IHeader itmh) { this->field.itmh = itmh; }

IHeader IPacket::get_itmh() { return this->field.itmh; }

void IPacket::set_payload(std::string payload) { this->field.payload = payload; }

std::string IPacket::get_payload() { return this->field.payload; }

void IPacket::set_bytes(std::string bytes)
{
    if (bytes.size() == 0)
    {
        throw Exception("error : bytes size must lager than 0.");
    }
    this->bytes = bytes;
    try
    {
        bytesToField();
    }
    catch (Exception & e)
    {
        throw(e);
    }
}

std::string IPacket::get_bytes()
{
    try
    {
        fieldToBytes();
    }
    catch (Exception & e)
    {
        throw(e);
    }
    return this->bytes;
}

void IPacket::dump()
{
    this->field.itmh.dump();
    std::cout << "Payload:";
    std::cout << this->field.payload << endl;
}

void sc_trace(sc_trace_file * tf, const IPacket & v, const std::string & name) {}

void FPacket::fieldToBytes()
{
    std::string headerBytes;
    try
    {
        headerBytes = this->field.ftmh.get_bytes();
        this->bytes = headerBytes.append(this->field.payload);
    }
    catch (Exception & e)
    {
        throw(e);
    }
}

void FPacket::bytesToField()
{
    int header_size = this->field.ftmh.get_size();
    if (this->bytes.size() <= 0)
    {
        throw Exception("error : bytes size must lager than 0.");
    }
    std::string header_bytes = this->bytes.substr(0, header_size);
    std::string payload_bytes = this->bytes.substr(header_size, this->bytes.size() - header_size);
    this->field.payload = payload_bytes;
    try
    {
        this->field.ftmh.set_bytes(header_bytes);
    }
    catch (Exception & e)
    {
        throw(e);
    }
}

void FPacket::set_ftmh(FHeader ftmh) { this->field.ftmh = ftmh; }

FHeader FPacket::get_ftmh() { return this->field.ftmh; }

void FPacket::set_payload(std::string payload) { this->field.payload = payload; }

std::string FPacket::get_payload() { return this->field.payload; }

void FPacket::set_bytes(std::string bytes)
{
    if (bytes.size() == 0)
    {
        throw Exception("error : bytes size must lager than 0.");
    }
    this->bytes = bytes;
    try
    {
        bytesToField();
    }
    catch (Exception & e)
    {
        throw(e);
    }
}

std::string FPacket::get_bytes()
{
    try
    {
        fieldToBytes();
    }
    catch (Exception & e)
    {
        throw(e);
    }
    return this->bytes;
}

void FPacket::dump()
{
    this->field.ftmh.dump();
    std::cout << "Payload:";
    std::cout << this->field.payload << endl;
}

void sc_trace(sc_trace_file * tf, const FPacket & v, const std::string & name) {}

void OPacket::fieldToBytes()
{
    std::string headerBytes;
    try
    {
        headerBytes = this->field.otmh.get_bytes();
        this->bytes = headerBytes.append(this->field.payload);
    }
    catch (Exception & e)
    {
        throw(e);
    }
}

void OPacket::bytesToField()
{
    int header_size = this->field.otmh.get_size();
    if (this->bytes.size() <= 0)
    {
        throw Exception("error : bytes size must lager than 0.");
    }
    std::string header_bytes = this->bytes.substr(0, header_size);
    std::string payload_bytes = this->bytes.substr(header_size, this->bytes.size() - header_size);
    this->field.payload = payload_bytes;
    try
    {
        this->field.otmh.set_bytes(header_bytes);
    }
    catch (Exception & e)
    {
        throw(e);
    }
}

void OPacket::set_otmh(OHeader otmh) { this->field.otmh = otmh; }

OHeader OPacket::get_otmh() { return this->field.otmh; }

void OPacket::set_payload(std::string payload) { this->field.payload = payload; }

std::string OPacket::get_payload() { return this->field.payload; }

void OPacket::set_bytes(std::string bytes)
{
    if (bytes.size() == 0)
    {
        throw Exception("error : bytes size must lager than 0.");
    }
    this->bytes = bytes;
    try
    {
        bytesToField();
    }
    catch (Exception & e)
    {
        throw(e);
    }
}

std::string OPacket::get_bytes()
{
    try
    {
        fieldToBytes();
    }
    catch (Exception & e)
    {
        throw(e);
    }
    return this->bytes;
}

void OPacket::dump()
{
    this->field.otmh.dump();
    std::cout << "Payload:";
    std::cout << this->field.payload << endl;
}

void sc_trace(sc_trace_file * tf, const OPacket & v, const std::string & name) {}
