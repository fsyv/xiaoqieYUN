#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

/**
 * 创建队列
 * @return 队列指针
 */
pQueue createQueue()
{
    pQueue queue = (pQueue)malloc(sizeof(Queue));

    if(!queue)
    {
        //申请内存失败

#ifdef Debug
        int errno;
        fprintf(stderr, "createQueue : %s\n", strerror(errno));
#endif
        return NULL;
    }
    memset(queue, 0, sizeof(Queue));
    queue->m_iMaxQueueLen = MAX_QUEUE_SIZE;
    queue->m_iQueueLen = 0;
    queue->p_vFront = NULL;
    queue->p_vRear = NULL;

    return queue;
}

/**
 * 销毁队列
 * @param queue 队列指针的地址
 */
void destroyQueue(pQueue *queue)
{
    if (!*queue)
        return;

    if ((*queue)->m_iQueueLen)
    {
#ifdef Debug
        int errno;
        fprintf(stderr, "destroyQueue : %s\n", strerror(errno));
#endif
    }
    free(*queue);
    *queue = NULL;
}

/**
 * 判断队列是否空
 * @param queue 队列指针
 * @return 1为空，0为不空
 */
int isEmpty(pQueue queue)
{
    return queue->m_iQueueLen == 0;
}

/**
 * 判断队列是否满
 * @param queue 队列指针
 * @return 1为满，0为不满
 */
int isFull(pQueue queue)
{
    return queue->m_iQueueLen >= queue->m_iMaxQueueLen;
}

/**
 * 入队
 * @param queue 队列指针
 * @param newData 入队数据
 */
void enQueue(pQueue queue, void *newData)
{
    if(isFull(queue))
    {
        //锁住
    }
    ++(queue->m_iQueueLen);
    queue->p_vRear = newData;
}
//出队
void *deQueue(pQueue queue)
{
    if(!isEmpty(queue))
    {
        --(queue->m_iQueueLen);
        return queue->p_vFront;
    }

#ifdef Debug
    fprintf(stderr, "deQueue : %s\n", "queue isEmpty!");
#endif
    return NULL;
}