#include "sendMsg.h"

#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>


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
int sendAckErrorMsg(int sockfd, ErrorMsg errorMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(ErrorMsg));
    bzero(msg, sizeof(Msg) + sizeof(ErrorMsg));

    msg->m_eMsgType = Ack_Error;
    msg->m_iMsgLen = sizeof(ErrorMsg);
    memcpy(msg->m_aMsgData, (void *)&errorMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, &msg);

    free(msg);
    return ret;
}

//发送消息
int sendMsg(int sockfd, Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    return send(sockfd, (void *)msg, sizeof(Msg) + msg->m_iMsgLen, 0);
}

