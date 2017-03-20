#ifndef SRC_QUEUE_SOCKETQUEUE_H
#define SRC_QUEUE_SOCKETQUEUE_H
/**
 * socket队列
 * @date 2017年 3月 13日
 * @version 1.0
 */

#include <netinet/in.h>

//最大队列数量
#define MAX_QUEUE_SIZE 256
#define SERVER_PORT 36975

typedef struct _ClientInfo{
    int m_iClientSocketfd;                  //客户端描述字
    u_int32_t m_uiNetworkAddr;              //网络地址
    u_int16_t m_usNetworkPort;              //网络端口
}ClientInfo;

typedef struct _SocketInfo{
    ClientInfo m_stClient;                  //客户端的socket
    struct _SocketInfo *p_stNext;
}SocketInfo, *pSocketInfo;

typedef struct _SocketQueue{
    int m_iMaxQueueLen;                     //最大队列
    int m_iQueueLen;                        //当前队列树
    pSocketInfo p_stFront;                  //队首
    pSocketInfo p_stRear;                   //队尾
}SocketQueue, *pSocketQueue;

//创建队列
pSocketQueue createSocketQueue();
//判断队列是否空
int isEmpty(pSocketQueue queue);
//判断队列是否满
int isFull(pSocketQueue queue);
//销毁队列
void destroySocketQueue(pSocketQueue *queue);
//入队
void enSocketQueue(pSocketQueue queue, ClientInfo ClientInfo);
//出队
ClientInfo deSocketQueue(pSocketQueue queue);

#endif