#include "serverSocket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../message/nstdmsgio.h"

/**
 * 关闭服务端soc关闭服务端socketfdketfd
 * @param serverSocketfd 服务器描述字
 */
void closeSocketfd(int serverSocketfd)
{
    shutdown(serverSocketfd, SHUT_RDWR);
    close(serverSocketfd);
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
    ev.events = EPOLLIN;

    //注册epoll事件
    epoll_ctl(epfd, EPOLL_CTL_ADD, serverSocketfd, &ev);

    //监听
    int err = listen(serverSocketfd, MAX_LISTEN);
    if(err)
    {
#ifdef Debug
        fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
        fprintf(stdout, "listen faild!!\n");
        closeSocketfd(serverSocketfd);
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

        printf("numberFds  = %d\n", numberFds);

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
                recvConnectionMsg(events[i].data.fd, epfd, &ev);
            }
        }
    }
}


/**
 * 服务器监听到新的Tcp socket请求
 * @param socketfd 服务器描述字
 * @param epfd epoll描述字
 * @param ev epoll事件
 */
void newConnection(int socketfd, int epfd, struct epoll_event *ev)
{
    struct sockaddr_in adress_client;
    int len = sizeof(struct sockaddr_in);

    //新连接
    int clientSocketfd = accept(socketfd, (struct sockaddr *)&adress_client, &len);

    if(clientSocketfd < 0)
    {
#ifdef Debug
        fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
        return;
    }

    setnblocking(clientSocketfd);

    //将新连接丢到epoll事件中
    ev->data.fd = clientSocketfd;
    //EPOLLIN 设置用于注册的读操作事件
    ev->events = EPOLLOIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, clientSocketfd, ev);
}

/**
 * 收到socket消息
 * @param socketfd 客户端描述字
 */
void recvConnectionMsg(int socketfd, int epfd, struct epoll_event *ev)
{
    Msg *msg = NULL;

    //接收缓存
    char *recvBuf = (char *)malloc((2 * RECV_BUF_MAX_SIZE + 1) * sizeof(char));
    memset(recvBuf, 0, 2 * RECV_BUF_MAX_SIZE * sizeof(char));

    //recvBuf指针
    char *pPosBuf = recvBuf;
    //实际接收到得字节数量
    int recvRet = 0;
    //消息长度
    int msgLen = 0;
    int clientSocketfd = socketfd;
    int msgStructLen = sizeof(Msg);

    while(recvRet = recv(clientSocketfd, pPosBuf, RECV_BUF_MAX_SIZE, 0))
    {
        //读数据错误
        if(recvRet < 0)
        {
#ifdef Debug
            fprintf(stderr, "recv : %s \n", strerror(errno));
#endif
            if(errno == EAGAIN)
            {
                //这次没有数据了，下次再来
                break;
            }
            else
            {
                ev->data.fd = clientSocketfd;
                epoll_ctl(epfd, EPOLL_CTL_DEL, clientSocketfd, ev);
                closeSocketfd(clientSocketfd);
                break;
            }
        }

        msgLen += recvRet;

        if (msgLen > 2 * RECV_BUF_MAX_SIZE)
        {
            //消息长度大于缓存长度
            exit(-1);
        }

        //如果收到包长度小于结构体长度，暂定为丢弃
        //实际可能会出现拆包情况，收到小于包长度得
        //数据包
        if(recvRet < msgStructLen)
        {
            //指正移到缓存后
            pPosBuf += recvRet;
            continue;
        }

        recvBuf[msgLen] = '\0';

        msg = (Msg *)recvBuf;

        //校验位是否正确，如果正确则执行下一步
        if(msg->m_uiCheckCrc != (unsigned int)0xAFAFAFAF)
        {
            //矫正
//            unsigned char crc[5];
//            memset(crc, 0xAF, 4);
        }

        if(msgLen < msgStructLen + msg->m_iMsgLen)
        {
            //拆包
            pPosBuf += recvRet;
            continue;
        }

        if(msgLen > msgStructLen + msg->m_iMsgLen)
        {
            //黏包
        }

        msgLen -= msgStructLen + msg->m_iMsgLen;

        //投递数据包
        recvMsg(clientSocketfd, msg, NULL);
    }
}
