#include "threadPool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//创建线程池
pThreadPool createThreadPool(int maxThreadNum)
{
    pThreadPool threadPool = NULL;

    threadPool = (pThreadPool)malloc(sizeof(ThreadPool));
    if(!threadPool)
    {
#ifdef Debug
        fprintf(stderr, "createThreadPool : %s \n", strerror(errno));
#endif
        fprintf(stdout, "createThreadPool faild!!\n");
        exit(-1);
    }

    memset(threadPool, 0, sizeof(ThreadPool));

    threadPool->m_iThreadNum = maxThreadNum;

    pthread_mutex_init(&(threadPool->taskmutex), NULL);
    pthread_mutex_init(&(threadPool->queuemutex), NULL);
    pthread_cond_init(&(threadPool->queue_not_empty), NULL);

    threadPool->m_pThreads = (pthread_t *)malloc(sizeof(pthread_t) * threadPool->m_iThreadNum);

    if(!threadPool->m_pThreads)
    {
#ifdef Debug
        fprintf(stderr, "createThreadPool : %s \n", strerror(errno));
#endif
        fprintf(stdout, "createThreadPool faild!!\n");
        exit(-1);
    }

    int i = 0;
    for (i = 0; i < threadPool->m_iThreadNum; ++i)
        pthread_create(threadPool->m_pThreads + i, NULL, threadpool_function, (void *)threadPool);

    return threadPool;
}

//往线程池任务添加任务
int addJobThreadPool(ThreadPool *threadPool, TaskQueue *taskQueue)
{
    if (!threadPool)
    {
#ifdef Debug
        fprintf(stderr, "addJobThreadPool : %s \n", "句柄无效");
#endif
        fprintf(stdout, "addJobThreadPool faild!!\n");
        return -1;
    }

    pthread_mutex_lock(&(threadPool->queuemutex));

    if (threadPool->front == NULL)
    {
        threadPool->front = threadPool->rear = taskQueue;
    }
    else
    {
        threadPool->rear->next = taskQueue;
        threadPool->rear = taskQueue;
    }
    pthread_cond_broadcast(&(threadPool->queue_not_empty));
    ++(threadPool->m_iQueueLen);

    pthread_mutex_unlock(&(threadPool->queuemutex));
}

//销毁线程池
void destroyThreadPool(ThreadPool *threadPool)
{
    pTaskQueue taskQueue = NULL;
    while(threadPool->front)
    {
        taskQueue = threadPool->front;
        threadPool->front = threadPool->front->next;
        free(taskQueue);
        taskQueue = NULL;
    }

    pthread_t *pthread;
    int i = 0;
    for(i = 0; i < threadPool->m_iThreadNum; ++i)
    {
        pthread = threadPool->m_pThreads + i;
        pthread_kill(pthread, 0);
        free(pthread);
        pthread = NULL;
    }

    free(threadPool);
    threadPool = NULL;
}

//线程函数
void *threadpool_function(void *arg)
{
    pThreadPool threadPool = (pThreadPool)arg;
    pTaskQueue taskQueue = NULL;
    while (1)
    {
        pthread_mutex_lock(&(threadPool->taskmutex));

        while(!threadPool->m_iQueueLen)
            pthread_cond_wait(&(threadPool->queue_not_empty), &(threadPool->taskmutex));

        pthread_mutex_unlock(&(threadPool->taskmutex));

        pthread_mutex_lock(&(threadPool->queuemutex));

        --(threadPool->m_iQueueLen);


        taskQueue = threadPool->front;
        if(threadPool->m_iQueueLen)
        {
            threadPool->front = threadPool->front->next;
        }
        else
        {
            threadPool->front = threadPool->rear = 0;
        }

        pthread_mutex_unlock(&(threadPool->queuemutex));

        (*(taskQueue->p_fCallBackFunction))(taskQueue->sockfd, taskQueue->p_vArg);

        if(taskQueue)
        {
            if(taskQueue->p_vArg)
            {
                free(taskQueue->p_vArg);
                taskQueue->p_vArg = NULL;
            }
            free(taskQueue);
            taskQueue = NULL;
        }
    }
}

