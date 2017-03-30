/**
 * LinxuServer main方法，主线程用于监听，一旦有用户来测创建用户线程
 * @date 2017年 3月 12日
 * @version 1.0
 */

#include <stdio.h>

#include "socket/serverSocket.h"


int main(int argc, char **argv)
{
    int sockfd = createSocketServer();
    listenClient(sockfd);
    closeSockfd(sockfd);
    return 0;
}