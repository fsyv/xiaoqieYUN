#include "sendMsg.h"

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

