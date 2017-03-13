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

#ifdef DEBUG
        int errno;
        fprintf(stderr, "createQueue : %s", strerror(errno));
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
#ifdef DEBUG
        int errno;
        fprintf(stderr, "createQueue : %s", strerror(errno));
#endif
    }
    free(*queue);
    *queue = NULL;
}