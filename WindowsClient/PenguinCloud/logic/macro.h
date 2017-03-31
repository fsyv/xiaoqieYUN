#ifndef MACRO_H
#define MACRO_H

typedef enum _MsgType{
    Ack_OK = 0,         //确定成功
    Ack_Error,         //确定错误
    Ack_Ready,         //准备就绪
    Login_Msg           //登录消息
}MsgType;

typedef struct _Msg{
    unsigned int m_uiCheckCrc;            //消息校验 0xAFAFAFAF
    MsgType m_eMsgType;				   		//消息类型
    int m_iMsgLen;							//消息长度
    char m_aMsgData[0];						//消息内容
}Msg, *pMsg;


#endif // MACRO_H
