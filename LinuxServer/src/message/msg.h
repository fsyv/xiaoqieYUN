//
// Created by cjy on 2017/3/21.
//

#ifndef LINUXSERVER_MESSAGE_MSG_H
#define LINUXSERVER_MESSAGE_MSG_H

#include "msgType.h"

typedef struct _Msg{
    unsigned int m_uiCheckCrc;            //消息校验 0xAFAFAFAF
    MsgType m_eMsgType;				   		//消息类型
    int m_iMsgLen;							//消息长度
    char m_aMsgData[0];						//消息内容
}Msg, *pMsg;

//确定成功消息
int sendAckOkMsg(int sockfd);
//确定失败消息
int sendAckErrorMsg(int sockfd);


#endif //LINUXSERVER_MESSAGE_MSG_H
