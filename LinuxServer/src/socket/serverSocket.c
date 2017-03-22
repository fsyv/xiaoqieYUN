#include "serverSocket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>

#include <pthread.h>

#include "../queue/socketQueue.h"
#include "../message/msg.h"

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
 * 设置socket为非拥塞
 * @param sockfd socket描述字
 */
void setnblocking(int sockfd)
{
    int opts;
    opts = fcntl(sockfd, F_GETFL);
    if(opts<0)
    {
#ifdef Debug
        fprintf(stderr, "setnblocking : %s \n", strerror(errno));
#endif
        close(sockfd);
        exit(-1);
    }

    opts = opts|O_NONBLOCK;
    if(fcntl(sockfd,F_SETFL,opts)<0)
    {
#ifdef Debug
        fprintf(stderr, "setnblocking : %s \n", strerror(errno));
#endif
        close(sockfd);
        exit(-1);
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

    //将服务端sockfd设置为费永塞
    setnblocking(sockfd);

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

    //创建socket队列
    pSocketQueue sQ = createSocketQueue();
    //从队列中读取clientSocket的线程
    pthread_t sQtoSoctetThread;
    pthread_create(&sQtoSoctetThread, NULL, queueThread, (void *)sQ);

    //客户端信息
    int clientSocketfd;
    struct sockaddr_in clientAddress;
    int clientAddressLen = sizeof(struct sockaddr_in);
    memset(&clientAddress, 0, clientAddressLen);

    //epoll
    //epoll_event结构体，用来创建和接收epoll事件
    struct epoll_event ev, events[MAX_LISTEN];
    //创建epoll fd
    int epfd = epoll_create(MAX_LISTEN + 1);

    ev.data.fd = serverSocketfd;
    ev.events = EPOLLIN|EPOLLET;

    //注册epoll事件
    epoll_ctl(epfd, EPOLL_CTL_ADD, serverSocketfd, &ev);

    //监听
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

    //一次事件的总数
    int numberFds = 0;
    int i = 0;
    while(1)
    {
        //等待
        numberFds = epoll_wait(epfd, events, MAX_LISTEN, EPOLL_TIME_OUT);

        //处理EPOLL_TIME_OUT内发生的所有事件
        for(i = 0; i < numberFds; ++i)
        {
            if (events[i].data.fd == serverSocketfd)
            {
                //新连接
                clientSocketfd = accept(serverSocketfd, (struct sockaddr *)&clientAddress, &clientAddressLen);
                if(clientSocketfd < 0)
                {
#ifdef Debug
                    fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
                    fprintf(stdout, "accept faild!!\n");
                    closeServersocketfd(serverSocketfd);
                    exit(-1);
                }

                //将新连接丢到epoll事件中
                ev.data.fd = clientSocketfd;
                //设置用于注测的读操作事件
                ev.events = EPOLLIN|EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clientSocketfd, &ev);

                //给客户端发送确认连接消息
                if(sendAckOkMsg(clientSocketfd) < 0)
                {
#ifdef Debug
                    fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
                    fprintf(stdout, "sendAckOkMsg faild!!\n");
                }
            }
            else if (events[i].events & EPOLLIN)
            {
                //收到消息
                clientSocketfd = events[i].data.fd;
                //如果收到得是确定连接消息，则把这个添加到socket队列里
            }
        }
    }


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


