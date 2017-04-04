#ifndef LINUXSERVER_QUEUE_THREADPOOL_H
#define LINUXSERVER_QUEUE_THREADPOOL_H

#include <pthread.h>



#define DEFAULT_THREAD_NUM 5

typedef struct _TaskQueue{
    void *(*p_fCallBackFunction)(void *arg);      //回调函数
    void *p_vArg;                                  //回调参数
    struct _TaskQueue *next;                       //下一个
}TaskQueue, *pTaskQueue;

typedef struct _ThreadPool{
    int m_iThreadNum;               //线程池数量
    TaskQueue *front;               //队首
    TaskQueue *rear;                //队尾
    int m_iQueueLen;                //队列中任务数量
    pthread_t *m_pThreads;          //许多线程
    pthread_mutex_t queuemutex;     //队列锁
    pthread_mutex_t taskmutex;      //任务锁
    pthread_cond_t queue_not_empty; //队列不为空的条件变量
}ThreadPool, *pThreadPool;

//创建线程池
pThreadPool createThreadPool(int maxThreadNum);
//往线程池任务添加任务
int addJobThreadPool(ThreadPool *threadPool, void *(*callback_function)(void *arg), void *arg);
//销毁线程池
void destroyThreadPool(ThreadPool *threadPool);
//线程函数
void *threadpool_function(void *arg);

#endif //LINUXSERVER_QUEUE_THREADPOOL_H
