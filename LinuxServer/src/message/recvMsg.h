#ifndef LINUXSERVER_MESSAGE_RECVMSG_H
#define LINUXSERVER_MESSAGE_RECVMSG_H

#include "msg.h"
#include "msgType.h"


//收到消息
int recvMsg(int sockfd, Msg *msg, void *arg);
//收到准备就绪消息
int recvReadyMsg(int sockfd, Msg *msg, void *arg);

#endif //LINUXSERVER_MESSAGE_RECVMSG_H
