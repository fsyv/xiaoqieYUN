
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>

#include "../queue/socketQueue.h"

#define MAX_LISTEN MAX_QUEUE_SIZE

/**
 * 关闭服务端soc关闭服务端socketfdketfd
 * @param serverSocketfd 服务器描述字
 */
void closeServersocketfd(int serverSocketfd)
{
    shutdown(serverSocketfd, SHUT_RDWR);
    close(serverSocketfd);
}

/**
 * 定时从队列中取用户队列
 * @param arg 队列的指针
 */
void *queueThread(void *arg)
{
    while(1)
    {
        usleep(1);
    }
}

/**
 * 创建服务器socket
 * @return 服务器描述字
 */
int createSocketServer()
{
    int errno = 0;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
#ifdef Debug
        fprintf(stderr, "createSocketServer : %s \n", strerror(errno));
#endif
        fprintf(stdout, "createSocketServer faild!!\n");
        exit(-1);
    }

#ifdef Debug
    fprintf(stdout, "serverSocet  created!!\n");
#endif

    struct sockaddr_in serverAddress;
    int serverAddressLen = sizeof(struct sockaddr_in);
    memset(&serverAddress, 0, serverAddressLen);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(SERVER_PORT);

#ifdef Debug
    fprintf(stdout, "Server Port at %d\n", SERVER_PORT);
#endif

    errno = bind(sockfd, (struct sockaddr *)&serverAddress, serverAddressLen);
    if(errno < 0)
    {
#ifdef Debug
        fprintf(stderr, "createSocketServer : %s \n", strerror(errno));
#endif
        fprintf(stdout, "bind faild!!\n");
        exit(-1);
    }
#ifdef Debug
    fprintf(stdout, "bind  created!!\n");
#endif

    return sockfd;
}

/**
 * 监听socket然后创建用户线程
 * @param serverSocketfd 服务器描述字
 */
void listenClient(int serverSocketfd)
{
    int errno;

    //创建socket队列
    pQueue sQ = createSocketQueue();
    //从队列中读取clientSocket的线程
    pthread_t sQtoSoctet;
    pthread_create(&sQtoSoctet, NULL, queueThread, (void *)sQ);

    errno = listen(serverSocketfd, MAX_LISTEN);
    if(errno)
    {
#ifdef Debug
        fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
        fprintf(stdout, "listen faild!!\n");
        closeServersocketfd(serverSocketfd);
    }

#ifdef Debug
    fprintf(stdout, "Max Listen : %d \n", MAX_LISTEN);
#endif

    int clientSocketfd;
    struct sockaddr_in clientAddress;
    int clientAddressLen = sizeof(struct sockaddr_in);

    SocketInfo clientSocketInfo;
    while(1)
    {
        printf("wait!!\n");
        clientSocketfd = accept(serverSocketfd, (struct sockaddr *)&clientAddress, &clientAddressLen);
        if(clientSocketfd < 0)
        {
#ifdef Debug
            fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
            fprintf(stdout, "listen faild!!\n");
            continue;
        }

        clientSocketInfo.m_iClientSocketfd = clientSocketfd;
        clientSocketInfo.m_stClientAddr = clientAddress;
        //加入队列
        enSocketQueue(sQ, clientSocketInfo);
    }

}


