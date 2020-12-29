#ifndef _XML_H_
#define _XML_H_

#include "stdio.h"
#include "stream.h"
#include "tinyxml.h"
#include <cstring>
#include <iostream>
#include <string>
#define F_SUCCESS 0
#define F_FAIL -1

template <class T> class XmlParse
{
public:
    int parse_xml(T & st_list);
};

template <class T> int XmlParse<T>::parse_xml(T & st_list)
{
    std::string str;
    IHeader itmh;
    Stream stream;
    IPacket ipacket_tmp;
    int pkt_cnt = 0;
    const char * xmlFile = "./packet.xml";
    TiXmlDocument doc;

    if (doc.LoadFile(xmlFile))
    {
        //       doc.Print();
    }
    else
    {
        std::cout << "can load parse xml " << std::endl;
        return F_FAIL;
    }

    st_list.removeAll();
    std::cout << "start parsing : " << std::endl;
    TiXmlElement * rootElement = doc.RootElement();                  // root元素
    TiXmlElement * streamElement = rootElement->FirstChildElement(); // stream�?
    for (; streamElement != NULL; streamElement = streamElement->NextSiblingElement())
    {
        stream.reset();
        TiXmlAttribute * attributeOfStream = streamElement->FirstAttribute(); //获得packet的name属�?
        for (; attributeOfStream != NULL; attributeOfStream = attributeOfStream->Next())
        {
            str = attributeOfStream->Name();
            if (str == "type")
            {
                if ((atoi(attributeOfStream->Value()) > 1) && (atoi(attributeOfStream->Value()) < 0))
                {
                    std::cout << "stream type error, scope<0-1> " << std::endl;
                    return F_FAIL;
                }
                stream.streamtype = atoi(attributeOfStream->Value());
                std::cout << attributeOfStream->Name() << " : " << (stream.streamtype ? "burst" : "continue")
                          << std::endl;
            }
            if (str == "bursts")
            {
                if (atoi(attributeOfStream->Value()) < 0)
                {
                    std::cout << "bursts error, scope<0- ...> " << std::endl;
                    return F_FAIL;
                }
                stream.burst = atoi(attributeOfStream->Value());
                std::cout << attributeOfStream->Name() << " : " << stream.burst << std::endl;
            }
            if (str == "loadpersec")
            {
                if (atoi(attributeOfStream->Value()) < 0)
                {
                    std::cout << "loadpersec error, scope<0- ...> " << std::endl;
                    return F_FAIL;
                }
                stream.loadpersec = atoi(attributeOfStream->Value());
                std::cout << attributeOfStream->Name() << " : " << stream.loadpersec << std::endl;
            }
            if (str == "mix")
            {
                if ((atoi(attributeOfStream->Value()) > 1) && (atoi(attributeOfStream->Value()) < 0))
                {
                    std::cout << "mix error, scope<0-1> " << std::endl;
                    return F_FAIL;
                }
                stream.mix = atoi(attributeOfStream->Value());
                std::cout << attributeOfStream->Name() << " : " << (stream.mix ? "true" : "false") << std::endl;
            }
            if (str == "TM_ID")
            {
                if ((atoi(attributeOfStream->Value()) > 2047) && (atoi(attributeOfStream->Value()) < 0))
                {
                    std::cout << "TM_ID error, scope<0-2047> " << std::endl;
                    return F_FAIL;
                }
                stream.TM_ID = atoi(attributeOfStream->Value());
                std::cout << attributeOfStream->Name() << " : " << stream.TM_ID << std::endl;
            }
        }

        TiXmlElement * packetElement = streamElement->FirstChildElement(); // packet
        std::cout << std::endl;
        std::cout << "packet info : " << std::endl;

        for (; packetElement != NULL; packetElement = packetElement->NextSiblingElement())
        {
            TiXmlAttribute * attributeOfPacket = packetElement->FirstAttribute(); //获得packet的name属�?
            for (; attributeOfPacket != NULL; attributeOfPacket = attributeOfPacket->Next())
            {
                std::cout << attributeOfPacket->Name() << " : " << attributeOfPacket->Value() << std::endl;
            }

            TiXmlElement * contentElement = packetElement->FirstChildElement(); //获得packet的第一个元�?
            for (; contentElement != NULL; contentElement = contentElement->NextSiblingElement())
            {
                //        cout  << " contentname =  "<< contentElement->Value() << std::endl;//获节点名
                std::string contentName = contentElement->Value();
                if (contentName == "ITMH")
                {
                    TiXmlElement * ITMHElement = contentElement->FirstChildElement();

                    for (; ITMHElement != NULL; ITMHElement = ITMHElement->NextSiblingElement())
                    {
                        std::string contactType = ITMHElement->Value();
                        std::string contactValue = ITMHElement->GetText();
                        unsigned type;

                        if (contactType == "itmh_type")
                        {
                            if (atoi(contactValue.c_str()) > 3)
                            {
                                std::cout << "itmh_type error, scope<0-3> " << std::endl;
                                return F_FAIL;
                            }
                            type = atoi(contactValue.c_str());
                            if (type == 0)
                            {
                                std::cout << "type 0 itmh header is not valid ! " << std::endl;
                            }
                            else
                            {
                                std::cout << "itmh_type : " << type << std::endl;
                            }
                        }

                        if (type == 0)
                        {
                            itmh.set_type(IHeader::EMPTY);
                            continue;
                        }
                        else if (type == 1)
                        {
                            itmh.set_type(IHeader::TDM);
                            std::cout << "name = " << contactType << std::endl;
                            if (contactType == "rsv")
                            {
                                if (atoi(contactValue.c_str()) > 0xfffff)
                                {
                                    std::cout << "rsv error, scope<0-0xfffff> " << std::endl;
                                    return F_FAIL;
                                }
                                //                           stream.pktdata.datafield.TYPE_A.rsv =
                                //                           atoi(contactValue.c_str()); cout << "rsv : " <<
                                //                           stream.pktdata.datafield.TYPE_A.rsv << std::std::endl;
                            }
                            if (contactType == "channel_num")
                            {
                                if (atoi(contactValue.c_str()) > 0x3ff)
                                {
                                    std::cout << "channel_num error, scope<0-0x3ff> " << std::endl;
                                    return F_FAIL;
                                }
                                itmh.set_channel_no(atoi(contactValue.c_str()));
                                std::cout << "channel_num : " << atoi(contactValue.c_str()) << std::endl << std::endl;
                            }
                        }
                        else if (type == 2)
                        {
                            itmh.set_type(IHeader::MULTICAST);
                            if (contactType == "tc")
                            {
                                if (atoi(contactValue.c_str()) > 7)
                                {
                                    std::cout << "tc error, scope<0-7> " << std::endl;
                                    return F_FAIL;
                                }
                                itmh.set_tc(atoi(contactValue.c_str()));
                                std::cout << "tc : " << atoi(contactValue.c_str()) << std::endl;
                            }
                            if (contactType == "dp")
                            {
                                if (atoi(contactValue.c_str()) > 7)
                                {
                                    std::cout << "dp error, scope<0-7> " << std::endl;
                                    return F_FAIL;
                                }
                                itmh.set_dp(atoi(contactValue.c_str()));
                                std::cout << "dp : " << atoi(contactValue.c_str()) << std::endl;
                            }
                            if (contactType == "rsv")
                            {
                                if (atoi(contactValue.c_str()) > 0x3f)
                                {
                                    std::cout << "rsv error, scope<0-0x3f> " << std::endl;
                                    return F_FAIL;
                                }
                                std::cout << "rsv : " << atoi(contactValue.c_str()) << std::endl;
                            }
                            if (contactType == "multicast_ID")
                            {
                                if (atoi(contactValue.c_str()) > 0x3ffff)
                                {
                                    std::cout << "multicast_ID error, scope<0-0x3ffff> " << std::endl;
                                    return F_FAIL;
                                }
                                itmh.set_multicast_id(atoi(contactValue.c_str()));
                                std::cout << "multicast_ID : " << atoi(contactValue.c_str()) << std::endl << std::endl;
                            }
                        }
                        else if (type == 3)
                        {
                            itmh.set_type(IHeader::UNICAST);
                            if (contactType == "tc")
                            {
                                if (atoi(contactValue.c_str()) > 7)
                                {
                                    std::cout << "tc error, scope<0-7> " << std::endl;
                                    return F_FAIL;
                                }
                                itmh.set_tc(atoi(contactValue.c_str()));
                                std::cout << "tc : " << atoi(contactValue.c_str()) << std::endl;
                            }
                            if (contactType == "dp")
                            {
                                if (atoi(contactValue.c_str()) > 7)
                                {
                                    std::cout << "dp error, scope<0-7> " << std::endl;
                                    return F_FAIL;
                                }
                                itmh.set_dp(atoi(contactValue.c_str()));
                                std::cout << "dp : " << atoi(contactValue.c_str()) << std::endl;
                            }
                            if (contactType == "calc_len_index")
                            {
                                if (atoi(contactValue.c_str()) > 0x1f)
                                {
                                    std::cout << "calc_len_index error, scope<0-0x1f> " << std::endl;
                                    return F_FAIL;
                                }
                                itmh.set_cal_len_index(atoi(contactValue.c_str()));
                                std::cout << "calc_len_index : " << atoi(contactValue.c_str()) << std::endl;
                            }
                            if (contactType == "rsv")
                            {
                                if (atoi(contactValue.c_str()) > 3)
                                {
                                    std::cout << "rsv error, scope<0-3> " << std::endl;
                                    return F_FAIL;
                                }
                                std::cout << "rsv : " << atoi(contactValue.c_str()) << std::endl;
                            }
                            if (contactType == "flowID")
                            {
                                if (atoi(contactValue.c_str()) >= 0x18000)
                                {
                                    std::cout << "flowID error, scope<0-0x18000> " << std::endl;
                                    return F_FAIL;
                                }
                                itmh.set_flow_id(atoi(contactValue.c_str()));
                                std::cout << "flowID : " << atoi(contactValue.c_str()) << std::endl << std::endl;
                            }
                        }
                        ipacket_tmp.set_itmh(itmh);
                    }
                }
                else if (contentName == "data")
                {
                    std::string contactValue = contentElement->GetText();
                    if (contactValue.length() > PACKET_PAYLOAD_MAX_SIZE)
                    {
                        std::cout << "datastring error, length scope<0-1024*128> " << std::endl;
                        return F_FAIL;
                    }
                    ipacket_tmp.set_payload(contactValue);
                    stream.packet_list.add(ipacket_tmp);
                    std::cout << "data : " << contactValue << std::endl;
                    std::cout << std::endl << std::endl;
                }
            }
        }

        st_list.add(stream);
    }

    return 0;
}
#endif
