#ifndef LINUXSERVER_MESSAGE_MSGTYPE_H
#define LINUXSERVER_MESSAGE_MSGTYPE_H


#include <elf.h>

//消息类型
typedef enum _MsgType{
    Ack_OK = 0,         //确定成功
    Ack_Error,         //确定错误
    Ack_Ready,         //准备就绪
    Login_Msg           //登录消息
}MsgType;

//准备就绪得消息结构
typedef struct _ReadyMsg{
    int m_iClientSockfd;           //客户端描述字
    uint32_t m_uiClientnaddress;   //客户端网络地址
}ReadyMsg, *pReadyMsg;


#endif //LINUXSERVER_MESSAGE_MSGTYPE_H
