#ifndef SRC_QUEUE_SOCKETQUEUE_H
#define SRC_QUEUE_SOCKETQUEUE_H
/**
 * 基于queue实现的socket队列
 * @date 2017年 3月 13日
 * @version 1.0
 */

#include "queue.h"

typedef struct _SocketQueue{
    int socketClient;                   //客户端的socket
    struct _SocketQueue *p_stNext;
}SocketQueue;

//创建队列
pQueue createSocketQueue();
//销毁队列
void destroySocketQueue(pQueue *queue);

#endif