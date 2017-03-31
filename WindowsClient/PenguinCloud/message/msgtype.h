#ifndef MSGTYPE_H
#define MSGTYPE_H

//消息类型
typedef enum _MsgType{
    Ack_OK = 0,         //确定成功
    Ack_Error,         //确定错误
    Ack_Ready,         //准备就绪
    Login_Msg           //登录消息
}MsgType;

//错误类型
typedef enum _ErrorType{
    DataPackError = 0        //错误得数据包
}ErrorType;
//发生了错误
typedef struct _ErrorMsg{
    ErrorType m_eErrorType;
}ErrorMsg, *pErrorMsg;

//准备就绪得消息结构
typedef struct _ReadyMsg{
    int m_iClientSockfd;           //客户端描述字
    unsigned int m_uiClientnaddress;   //客户端网络地址
}ReadyMsg, *pReadyMsg;

#endif // MSGTYPE_H
