/*
 * @Description:
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:41:21
 */
#ifndef _CRC_H_
#define _CRC_H_
#include <stdint.h>

#define CRC16_POLY_CCITT 0x1021
#define CRC16_INIT_CCITT 0x0000
#define CRC16_FINAL_CCITT 0x0000
#define CRC16_POLY_X25 0x1021
#define CRC16_INIT_X25 0xFFFF
#define CRC16_FINAL_X25 0xFFFF
#define CRC16_POLY_IBM 0x8005
#define CRC16_INIT_IBM 0x0000
#define CRC16_FINAL_IBM 0x0000

#define CRC32_POLY_STD 0x04C11DB7
#define CRC32_INIT_STD 0xFFFFFFFF
#define CRC32_FINAL_STD 0xFFFFFFFF
#define CRC32_POLY_POSIX 0x04C11DB7
#define CRC32_INIT_POSIX 0x00000000
#define CRC32_FINAL_POSIX 0xFFFFFFFF

uint16_t crc16(unsigned char *addr, int num, uint16_t poly, uint16_t crc, uint16_t final);
uint16_t crc16_CCITT(unsigned char *addr, int num);
uint16_t crc16_X25(unsigned char *addr, int num);
uint16_t crc16_IBM(unsigned char *addr, int num);

uint32_t crc32(unsigned char *addr, int num, uint32_t poly, uint32_t crc, uint32_t final);
uint32_t crc32_STD(unsigned char *addr, int num);
uint32_t crc32_POSIX(unsigned char *addr, int num);

#endif // _CRC_H_