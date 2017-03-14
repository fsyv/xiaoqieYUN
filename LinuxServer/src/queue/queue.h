#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H
/**
 * 队列的基本操作
 * @date 2017年 3月 13日
 * @version 1.0
 */

//最大队列数量
#define MAX_QUEUE_SIZE 256

typedef struct _Queue{
    int m_iMaxQueueLen;     //最大队列
    int m_iQueueLen;        //当前队列树
    void *p_vFront;         //队首
    void *p_vRear;           //队尾
}Queue, *pQueue;

//创建队列
pQueue createQueue();
//销毁队列
void destroyQueue(pQueue *queue);
//判断队列是否空
int isEmpty(pQueue queue);
//判断队列是否满
int isFull(pQueue queue);
//入队
void enQueue(pQueue queue, void *newData);
//出队
void *deQueue(pQueue queue);

#endif