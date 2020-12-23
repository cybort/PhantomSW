/*
 * @Description: Crc vertify
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:41:01
 */
#include "crc.h"

/**
 * Calculating CRC-16 in 'C'
 * @para addr, start of data
 * @para num, length of data
 * @para crc, incoming CRC
 */
uint16_t crc16(unsigned char *addr, int num, uint16_t poly, uint16_t crc, uint16_t final)
{
    int i;
    for (; num > 0; num--) /* Step through bytes in memory */
    {
        crc = crc ^ (*addr++ << (8 * sizeof(uint16_t) - 8)); /* Fetch byte from memory, XOR into CRC top byte*/
        for (i = 0; i < 8; i++)                              /* Prepare to rotate 8 bits */
        {
            if (crc & 0x8000)            /* b15 is set... */
                crc = (crc << 1) ^ poly; /* rotate and XOR with polynomic */
            else                         /* b15 is clear... */
                crc <<= 1;               /* just rotate */
        }                                /* Loop for 8 bits */
        crc &= 0xFFFF;                   /* Ensure CRC remains 16-bit value */
    }                                    /* Loop until num=0 */
    return (crc ^ final);                /* Return updated CRC */
}

uint16_t crc16_CCITT(unsigned char *addr, int num)
{
    return crc16(addr, num, CRC16_POLY_CCITT, CRC16_INIT_CCITT, CRC16_FINAL_CCITT);
}

uint16_t crc16_X25(unsigned char *addr, int num)
{
    return crc16(addr, num, CRC16_POLY_X25, CRC16_INIT_X25, CRC16_FINAL_X25);
}

uint16_t crc16_IBM(unsigned char *addr, int num)
{
    return crc16(addr, num, CRC16_POLY_IBM, CRC16_INIT_IBM, CRC16_FINAL_IBM);
}

uint32_t crc32(unsigned char *addr, int num, uint32_t poly, uint32_t crc, uint32_t final)
{
    int i;
    for (; num > 0; num--) /* Step through bytes in memory */
    {
        crc = crc ^ (*addr++ << (8 * sizeof(uint32_t) - 8)); /* Fetch byte from memory, XOR into CRC top byte*/
        for (i = 0; i < 8; i++)                              /* Prepare to rotate 8 bits */
        {
            if (crc & 0x80000000)        /* b31 is set... */
                crc = (crc << 1) ^ poly; /* rotate and XOR with polynomic */
            else                         /* b31 is clear... */
                crc <<= 1;               /* just rotate */
        }                                /* Loop for 8 bits */
        crc &= 0xFFFFFFFF;               /* Ensure CRC remains 32-bit value */
    }                                    /* Loop until num=0 */
    return (crc ^ final);                /* Return updated CRC */
}

uint32_t crc32_STD(unsigned char *addr, int num)
{
    return crc32(addr, num, CRC32_POLY_STD, CRC32_INIT_STD, CRC32_FINAL_STD);
}

uint32_t crc32_POSIX(unsigned char *addr, int num)
{
    return crc32(addr, num, CRC32_POLY_POSIX, CRC32_INIT_POSIX, CRC32_FINAL_POSIX);
}