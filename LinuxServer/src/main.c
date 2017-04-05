/**
 * LinxuServer main方法，主线程用于监听，一旦有用户来测创建用户线程
 * @date 2017年 3月 12日
 * @version 1.0
 */

#include <stdio.h>

#include <pthread.h>

#include "socket/serverSocket.h"
#include "socket/serverFileSocket.h"
#include "queue/threadPool.h"

//全局线程池
ThreadPool *m_pThreadPool = NULL;

int main(int argc, char **argv)
{
    m_pThreadPool = createThreadPool(DEFAULT_THREAD_NUM);

    pthread_t filePthread;
    pthread_create(&filePthread, NULL, createServerFileSocket, NULL);

    int sockfd = createSocketServer();
    listenClient(sockfd);
    closeSockfd(sockfd);

    destroyThreadPool(m_pThreadPool);
    return 0;
}