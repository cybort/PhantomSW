/*
 * @Description: 
 * @Author: f21538
 * @Date: 2020-12-28 14:15:55
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-28 14:18:17
 */
#include "ConfigDB.h"
#include "ConfigResolver.h"
// socket
#define LOCALHOST                                                                                                      \
    (ConfigResolver::GetInstance()                                                                                     \
         .get_string("port", "LOCALHOST", "127.0.0.1")                                                                 \
         .c_str()) //"10.114.220.163" //"127.0.0.1"
#define SW_IP                                                                                                          \
    (ConfigResolver::GetInstance().get_string("port", "SW_IP", "127.0.0.1").c_str()) //"10.114.220.163"//"10.132.52.54"
#define LISTEN_SOCKETS_NUM (ConfigResolver::GetInstance().get_int("port", "LISTEN_SOCKETS_NUM", 18))
#define SEND_SOCKETS_NUM (ConfigResolver::GetInstance().get_int("port", "SEND_SOCKETS_NUM", 18))
#define TM_BASE_SERVER_PORT (ConfigResolver::GetInstance().get_int("port", "TM_BASE_SERVER_PORT", 10000))
#define SW_BASE_SERVER_PORT                                                                                            \
    (ConfigResolver::GetInstance().get_int("port", "SW_BASE_SERVER_PORT", 11000)) // 10024//50001
#define STREAM_SEND_BASE_PORT (ConfigResolver::GetInstance().get_int("port", "STREAM_SEND_BASE_PORT", 12000))
#define HOST_PORT (ConfigResolver::GetInstance().get_int("port", "HOST_PORT", 13000))
#define STREAM_SEND_PORT (STREAM_SEND_BASE_PORT + SRC_TM_ID)

/*2+2 predefine*/
#define SW0_IP (ConfigResolver::GetInstance().get_string("port", "SW0_IP", "127.0.0.1"))//"10.114.20.107"
#define SW1_IP (ConfigResolver::GetInstance().get_string("port", "SW1_IP", "127.0.0.1"))//"10.114.20.169"
#define SW0_BA_PORT (SW_BASE_SERVER_PORT)
#define SW1_BA_PORT (ConfigResolver::GetInstance().get_int("port", "SW1_BASE_SERVER_PORT", 12000))

#define SRC_TM_ID (ConfigResolver::GetInstance().get_int("port", "SRC_TM_ID", 0))

#define TM_LINK_NUM 18
#define SW_LINK_NUM 18

// cell & bandiwidth
#define TM_CELL_PER_CLOCK_LIMIT 2
#define SW_CELL_PER_CLOCK_LIMIT 8
#define PKT_DATA_BANDWIDTH 160
#define MIN_CELL 64
#define MID_CELL 128
#define MAX_CELL 256

// tm load balancing
#define USE_RANDOM_LOAD_BALANCING 1

// signal
#define BIND_SIG(type, input, output, name)                                                                            \
    sc_signal<type> name##_temp;                                                                                       \
    input(name##_temp);                                                                                                \
    output(name##_temp);
