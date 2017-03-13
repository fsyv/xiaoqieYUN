#include "socketQueue.h"


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