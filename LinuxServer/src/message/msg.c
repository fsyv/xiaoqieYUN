#include "msg.h"

#include <sys/socket.h>
#include <string.h>

//确定成功消息
int sendAckOkMsg(int sockfd)
{
    Msg msg;
    bzero(&msg, sizeof(Msg));

    msg.m_eMsgType = Ack_OK;
    msg.m_iMsgLen = 0;

    return sendMsg(sockfd, &msg);
}

//确定失败消息
int sendAckErrorMsg(int sockfd)
{
    Msg msg;
    bzero(&msg, sizeof(Msg));

    msg.m_eMsgType = Ack_Error;
    msg.m_iMsgLen = 0;

    return sendMsg(sockfd, &msg);
}

//发送消息
int sendMsg(int sockfd, Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    return send(sockfd, (void *)msg, sizeof(Msg) + msg->m_iMsgLen, 0);
}

//收到消息
int recvMsg(int sockfd, Msg *msg)
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
            recvReadyMsg(sockfd, msg);
            break;
    }
}

/**
 * 收到准备就绪消息
 * @param sockfd 消息得句柄
 * @param msg 消息结构体
 * @return
 */
int recvReadyMsg(int sockfd, Msg *msg) {
    ReadyMsg readyMsg;
    memcpy(&readyMsg, msg->m_aMsgData, msg->m_iMsgLen);

    extern pSocketQueue sQ;

    //将这条数据入队
    enSocketQueue(sQ, readyMsg.m_stClientInfo);

    return 0;
}
