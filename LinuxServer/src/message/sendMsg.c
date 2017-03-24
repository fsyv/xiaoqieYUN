#include "sendMsg.h"

#include <unistd.h>

//发送消息
int sendMsg(int sockfd, Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    return send(sockfd, (void *)msg, sizeof(Msg) + msg->m_iMsgLen);
}

