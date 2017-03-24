//
// Created by cjy on 2017/3/21.
//

#ifndef MESSAGE_LINUXSERVER_MSGTYPE_H_H
#define MESSAGE_LINUXSERVER_MSGTYPE_H_H

//消息类型
typedef enum _MsgType{
    Ack_OK = 0,         //确定成功
    Ack_Error,         //确定错误
    Ack_Ready,         //准备就绪
    Login_Msg           //登录消息
}MsgType;


#endif //MESSAGE_LINUXSERVER_MSGTYPE_H_H
