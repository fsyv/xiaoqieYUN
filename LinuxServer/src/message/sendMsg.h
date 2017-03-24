#ifndef LINUXSERVER_MESSAGE_SENDMSG_H
#define LINUXSERVER_MESSAGE_SENDMSG_H

#include "../message/msgType.h"
#include "../message/msg.h"

//发送消息
int sendMsg(int sockfd, Msg *msg);

#endif //LINUXSERVER_MESSAGE_SENDMSG_H
