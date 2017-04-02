#include "recvMsg.h"

#include <stdio.h>

#include <string.h>

/**
 * 收到消息
 * @param sockfd
 * @param msg
 * @param arg 传参
 * @return
 */
void recvMsg(int sockfd, Msg *msg)
{
    printf("type : %d\n", msg->m_eMsgType);

    switch (msg->m_eMsgType){
        case Ack_OK:
#ifdef Debug
            fprintf(stdout, "Ack_OK\n");
#endif
            //确定成功
            break;
        case Ack_Error:
#ifdef Debug
            fprintf(stdout, "Ack_Error\n");
#endif
            //确定错误
            break;
        case Ack_Ready:
#ifdef Debug
            fprintf(stdout, "Ack_Ready\n");
#endif
            //准备就绪
            recvReadyMsg(sockfd, msg);
            break;
        case Put_Login:
#ifdef Debug
            fprintf(stdout, "Put_Login\n");
#endif
            //登录消息
            break;
    }
}

/**
 * 收到准备就绪消息
 * @param sockfd 消息得句柄
 * @param msg 消息结构体
 * @param arg 传参
 * @return
 */
void recvReadyMsg(int sockfd, Msg *msg)
{
    ReadyMsg readyMsg;
    memcpy(&readyMsg, msg->m_aMsgData, msg->m_iMsgLen);

    return 0;
}