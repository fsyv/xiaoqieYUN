#ifndef LINUXSERVER_MESSAGE_SENDMSG_H
#define LINUXSERVER_MESSAGE_SENDMSG_H

#include "msg.h"
#include "msgType.h"

//确定成功消息
int sendAckOkMsg(int sockfd);
//确定失败消息
int sendAckErrorMsg(int sockfd);

//发送消息
int sendMsg(int sockfd, Msg *msg);

#endif //LINUXSERVER_MESSAGE_SENDMSG_H
