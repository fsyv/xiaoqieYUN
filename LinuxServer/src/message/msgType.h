//
// Created by cjy on 2017/3/21.
//

#ifndef LINUXSERVER_MESSAGE_MSGTYPE_H
#define LINUXSERVER_MESSAGE_MSGTYPE_H

//消息类型
typedef enum _MsgType{
    Ack_OK = 0,         //确定成功
    Ack_Error          //确定错误
}MsgType;


#endif //LINUXSERVER_MESSAGE_MSGTYPE_H
