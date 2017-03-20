#include "socketQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

/**
 * 创建一个socket队列
 * @return 队列指针
 */
pSocketQueue createSocketQueue()
{
    pSocketQueue queue = (pSocketQueue)malloc(sizeof(SocketQueue));

    if(!queue)
    {
        //申请内存失败
#ifdef Debug
        fprintf(stderr, "createQueue : %s\n", strerror(errno));
#endif
        return NULL;
    }
    memset(queue, 0, sizeof(SocketQueue));
    queue->m_iMaxQueueLen = MAX_QUEUE_SIZE;
    queue->m_iQueueLen = 0;
    queue->p_stFront = NULL;
    queue->p_stRear = NULL;

    return queue;
}

/**
 * 判断队列是否空
 * @param queue 队列指针
 * @return 1为空，0为不空
 */
int isEmpty(pSocketQueue queue)
{
    return queue->m_iQueueLen == 0;
}

/**
 * 判断队列是否满
 * @param queue 队列指针
 * @return 1为满，0为不满
 */
int isFull(pSocketQueue queue)
{
    return queue->m_iQueueLen >= queue->m_iMaxQueueLen;
}

/**
 * 销毁一个队列
 * @param socketQueue 队列指针的地址
 */
void destroySocketQueue(pSocketQueue *queue)
{
    if (!*queue)
        return;

    //如果队列不为空，则先出队
    while(!isEmpty(*queue))
        deSocketQueue(*queue);

    free(*queue);
    *queue = NULL;
}

/**
 * socket队列入队操作
 * @param queue socket队列指针
 * @param socketInfo 入队的数据
 */
void enSocketQueue(pSocketQueue queue, ClientInfo ClientInfo)
{
    if(isFull(queue))
    {
        //锁住
    }

    pSocketInfo newData = (pSocketInfo)malloc(sizeof(SocketInfo));
    memset(newData, 0, sizeof(SocketInfo));

    newData->m_stClient = ClientInfo;
    newData->p_stNext = NULL;

    if(isEmpty(queue))
        queue->p_stFront = newData;
    else
        queue->p_stRear->p_stNext = newData;

    ++(queue->m_iQueueLen);
    queue->p_stRear = newData;
}

/**
 * socket队列出队操作
 * @param queue socket队列指针
 * @return 出队的数据
 */
ClientInfo deSocketQueue(pSocketQueue queue)
{
    if(!isEmpty(queue))
    {
        --(queue->m_iQueueLen);
        pSocketInfo deData = queue->p_stFront;
        queue->p_stFront = deData->p_stNext;

        ClientInfo clientInfo = deData->m_stClient;

        free(deData);
        deData = NULL;

        return clientInfo;
    }

#ifdef Debug
    fprintf(stderr, "deSocketQueue : %s\n", "queue isEmpty!");
#endif
}