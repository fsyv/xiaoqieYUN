#ifndef MSG_H
#define MSG_H

#include"msgtype.h"

typedef struct _Msg{
    unsigned int m_uiCheckCrc;              //消息校验 0xAFAFAFAF
    MsgType m_eMsgType;				   		//消息类型
    int m_iMsgLen;							//消息长度
    char m_aMsgData[0];						//消息内容
}Msg, *pMsg;


#endif // MSG_H
