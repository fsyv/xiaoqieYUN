#include "socketQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 创建一个socket队列
 * @return 队列指针
 */
pQueue createSocketQueue()
{
    return createQueue();
}

/**
 * 销毁一个队列
 * @param socketQueue 队列指针的地址
 */
void destroySocketQueue(pQueue *queue)
{
    destroyQueue(queue);
}

/**
 * socket队列入队操作
 * @param queue socket队列指针
 * @param socketInfo 入队的数据
 */
void enSocketQueue(pQueue queue, SocketInfo socketInfo)
{
    pSocketQueue newSokcetData = (pSocketQueue)malloc(sizeof(SocketQueue));
    memset(newSokcetData, 0, sizeof(SocketQueue));

    newSokcetData->m_stClient = socketInfo;

    if(isEmpty(queue))
    {
        queue->p_vFront = (void *)newSokcetData;
    }
    else
    {
        pSocketQueue socketQueueRear = (pSocketQueue)queue->p_vRear;
        socketQueueRear->p_stNext = (void *)newSokcetData;
    }

    enQueue(queue, newSokcetData);
}

/**
 * socket队列出队操作
 * @param queue socket队列指针
 * @return 出队的数据
 */
SocketInfo deSocketQueue(pQueue queue)
{
    pSocketQueue deData = (pSocketQueue)deQueue(queue);
    queue->p_vFront = (void *)deData->p_stNext;

    SocketInfo socketInfo = deData->m_stClient;

    free(deData);
    deData = NULL;
    return socketInfo;
}