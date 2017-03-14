#ifndef SRC_QUEUE_SOCKETQUEUE_H
#define SRC_QUEUE_SOCKETQUEUE_H
/**
 * 基于queue实现的socket队列
 * @date 2017年 3月 13日
 * @version 1.0
 */

#include "queue.h"

#include <netinet/in.h>

typedef struct _SocketInfo{
    int m_iClientSocketfd;                  //客户端描述字
    struct sockaddr_in m_stClientAddr;      //客户端地址和端口
}SocketInfo;

typedef struct _SocketQueue{
    SocketInfo m_stClient;                   //客户端的socket
    struct _SocketQueue *p_stNext;
}SocketQueue, *pSocketQueue;

//创建队列
pQueue createSocketQueue();
//销毁队列
void destroySocketQueue(pQueue *queue);
//入队
void enSocketQueue(pQueue queue, SocketInfo socketInfo);
//出队
SocketInfo deSocketQueue(pQueue queue);

#endif