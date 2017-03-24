/**
 * LinxuServer main方法，主线程用于监听，一旦有用户来测创建用户线程
 * @date 2017年 3月 12日
 * @version 1.0
 */

#include <stdio.h>

#include "queue/socketQueue.h"
#include "socket/serverSocket.h"

//全局队列指针
pSocketQueue sQ;

int main(int argc, char **argv)
{
    //创建socket队列
    sQ = createSocketQueue();

    int sockfd = createSocketServer();
    listenClient(sockfd);
    closeServersocketfd(sockfd);

    //清除队列
    destroySocketQueue(&sQ);
    return 0;
}