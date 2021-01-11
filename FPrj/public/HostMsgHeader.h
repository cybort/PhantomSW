/*
 * @Author: your name
 * @Date: 2020-12-23 11:03:07
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-05 10:22:12
 * @Description: file content
 */
#ifndef _HOST_MSG_HEADER_
#define _HOST_MSG_HEADER_

#define MSG_ID_HOST_RETURN_ERROR (0x7777U)
#define MSG_ID_HOST_RETURN_OK (0x8888U)

enum HOST_MSG_TYPE
{
    MSG_ID_HOST_READ = 0,
    MSG_ID_HOST_WRITE,
    MSG_ID_HOST_BUTT,
};

union HOST_MSG_HEADER
{
    struct
    {
        int uiMsgSeq;            /* 消息流水号 */
        int uiSize;              /* paylaod 有效长度 */
        HOST_MSG_TYPE uiMsgType; /* 消息类型 */
    };
    char bytes[];
};

#endif