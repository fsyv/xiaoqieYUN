
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

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
    int err = 0;
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

    err = bind(sockfd, (struct sockaddr *)&serverAddress, serverAddressLen);
    if(err < 0)
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
    int err;

    err = listen(serverSocketfd, MAX_LISTEN);
    if(err)
    {
#ifdef Debug
        fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
        fprintf(stdout, "listen faild!!\n");
        closeServersocketfd(serverSocketfd);
        exit(-1);
    }

#ifdef Debug
    fprintf(stdout, "Max Listen : %d \n", MAX_LISTEN);
#endif

    //创建socket队列
    pSocketQueue sQ = createSocketQueue();
    //从队列中读取clientSocket的线程
    pthread_t sQtoSoctetThread;
    pthread_create(&sQtoSoctetThread, NULL, queueThread, (void *)sQ);

    int clientSocketfd;
    struct sockaddr_in clientAddress;
    int clientAddressLen = sizeof(struct sockaddr_in);
    memset(&clientAddress, 0, clientAddressLen);

    ClientInfo clientSocketInfo;
    while(clientSocketfd = accept(serverSocketfd, (struct sockaddr *)&clientAddress, &clientAddressLen))
    {
        if(clientSocketfd < 0)
        {
#ifdef Debug
            fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
            fprintf(stdout, "accept faild!!\n");
            break;
        }

        clientSocketInfo.m_iClientSocketfd = clientSocketfd;
        clientSocketInfo.m_uiNetworkAddr = clientAddress.sin_addr.s_addr;
        clientSocketInfo.m_usNetworkPort = clientAddress.sin_port;

        //加入队列
        enSocketQueue(sQ, clientSocketInfo);
    }

    //关闭队列线程
    pthread_kill(sQtoSoctetThread, 0);
    //清除队列
    destroySocketQueue(&sQ);
}


