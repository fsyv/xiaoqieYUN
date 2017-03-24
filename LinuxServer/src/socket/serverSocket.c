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
    //epoll
    //epoll_event结构体，用来创建和接收epoll事件
    struct epoll_event ev, events[MAX_LISTEN];
    //创建epoll fd
    int epfd = epoll_create(MAX_LISTEN + 1);

    ev.data.fd = serverSocketfd;
    ev.events = EPOLLIN|EPOLLET;

    //注册epoll事件
    epoll_ctl(epfd, EPOLL_CTL_ADD, serverSocketfd, &ev);

    //创建监听处理队列
    extern pSocketQueue sQ;
    pthread_t sQtoSoctetThread;
    pthread_create(&sQtoSoctetThread, NULL, queueThread, (void *)sQ);

    //监听
    int err = listen(serverSocketfd, MAX_LISTEN);
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
        //这里处理了能够正确入队socket，不能正确
        //入队得socket还没有想好怎么处理
        for(i = 0; i < numberFds; ++i)
        {
            if (events[i].data.fd == serverSocketfd)
            {
                //新连接
                newConnection(events[i].data.fd, epfd, &ev);
            }
            else if (events[i].events & EPOLLIN)
            {
                //收到消息
                recvNewConnectionMsg(events[i].events, epfd, &ev);
            }
        }
    }

    //关闭队列线程
    pthread_kill(sQtoSoctetThread, 0);
}

/**
 * 服务器监听到新的Tcp socket请求
 * @param socketfd 服务器描述字
 * @param epfd epoll描述字
 * @param ev epoll事件
 */
void newConnection(int socketfd, int epfd, struct epoll_event *ev)
{
    //新连接
    int clientSocketfd = accept(socketfd, NULL, NULL);
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
    ev->data.fd = clientSocketfd;
    //EPOLLIN 设置用于注册的读操作事件
    //EPOLLONESHOT 这个事件只会被触发一次，然后就会清除出事件队列
    ev->events = EPOLLIN|EPOLLONESHOT;
    epoll_ctl(epfd, EPOLL_CTL_ADD, clientSocketfd, ev);

    //给客户端发送确认连接消息
    if(sendAckOkMsg(clientSocketfd) < 0)
    {
#ifdef Debug
        fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
        fprintf(stdout, "sendAckOkMsg faild!!\n");
    }
}

/**
 * 还没入队得新连接收到确定连接得消息
 * @param socketfd 客户端描述字
 * @param epfd epoll描述字
 * @param ev epoll事件
 */
void recvNewConnectionMsg(int socketfd, int epfd, struct epoll_event *ev)
{
    //接收缓存
    char recvBuf[RECV_BUF_MAX_SIZE + 1];
    bzero(recvBuf, RECV_BUF_MAX_SIZE);
    //实际接收到得字节数量
    int recvRet = 0;
    int clientSocketfd = socketfd;
    //如果收到得是确定连接消息，则把这个添加到socket队列里

    recvRet = recv(clientSocketfd, recvBuf, RECV_BUF_MAX_SIZE, 0);

    //读数据错误
    if(recvRet < 0)
    {
#ifdef Debug
        fprintf(stderr, "recv : %s \n", strerror(errno));
#endif
        //从epoll里面清除这个事件
    }

    //如果收到包长度小于结构体长度，暂定为丢弃
    //实际可能会出现拆包情况，收到小于包长度得
    //数据包
    if(recvRet < sizeof(Msg))
    {

    }

    recvBuf[recvRet] = '\0';

    Msg *msg = (Msg *)recvBuf;

    //校验位是否正确，如果正确则执行下一步
    if(msg->m_uiCheckCrc != (unsigned int)0xAFAFAFAF)
    {

    }

    //继续提交消息
    recvMsg(clientSocketfd, msg);
}

