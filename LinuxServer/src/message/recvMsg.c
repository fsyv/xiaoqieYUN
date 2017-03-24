#include "recvMsg.h"

#include <string.h>

#include "../queue/socketQueue.h"

/**
 * 收到消息
 * @param sockfd
 * @param msg
 * @param arg 传参
 * @return
 */
int recvMsg(int sockfd, Msg *msg, void *arg)
{
    switch (msg->m_eMsgType){
        case Ack_OK:
            //确定成功
            break;
        case Ack_Error:
            //确定错误
            break;
        case Ack_Ready:
            //准备就绪
            recvReadyMsg(sockfd, msg, arg);
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
int recvReadyMsg(int sockfd, Msg *msg, void *arg)
{
    ReadyMsg readyMsg;
    memcpy(&readyMsg, msg->m_aMsgData, msg->m_iMsgLen);

    pSocketQueue sQ = (pSocketQueue)arg;

    //将这条数据入队
    enSocketQueue(sQ, readyMsg.m_stClientInfo);

    return 0;
}