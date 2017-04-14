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
#include "../tools/tools.h"
#include "../operating/serverOperating.h"
#include "../queue/threadPool.h"


//创建响应服务器
void createServerService()
{
    int sockfd = createSocketServer(SERVER_PORT);
    if(sockfd)
        listenClient(sockfd);
    closeSockfd(sockfd);
}
//创建文件服务器
void *createFileServer(void *arg)
{
    int sockfd = createSocketServer(FILE_SERVER_PORT);
    if(sockfd)
        fileServerListen(sockfd);
    closeSockfd(sockfd);
}

/**
 * 关闭服务端soc关闭服务端socketfdketfd
 * @param serverSocketfd 服务器描述字
 */
void closeSockfd(int sockfd)
{
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
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

    printf("opts = %d\n", opts);
    if(fcntl(sockfd,F_SETFL,opts)<0)
    {
#ifdef Debug
        fprintf(stderr, "setnblocking : %s \n", strerror(errno));
#endif
        close(sockfd);
        exit(-1);
    }
}

//设置socket为拥塞
void setblocking(int sockfd)
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

    opts = O_RDWR;
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
int createSocketServer(unsigned int port)
{
    int err = 0;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
#ifdef Debug
        fprintf(stderr, "createSocketServer : %s \n", strerror(errno));
#endif
        fprintf(stdout, "createSocketServer faild!!\n");
        return 0;
    }

#ifdef Debug
    fprintf(stdout, "serverSocet  created!!\n");
#endif

    //将服务端sockfd设置为非拥塞
    setnblocking(sockfd);

    struct sockaddr_in serverAddress;
    int serverAddressLen = sizeof(struct sockaddr_in);
    memset(&serverAddress, 0, serverAddressLen);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

#ifdef Debug
    fprintf(stdout, "Server Port at %d\n", port);
#endif

    err = bind(sockfd, (struct sockaddr *)&serverAddress, serverAddressLen);
    if(err < 0)
    {
#ifdef Debug
        fprintf(stderr, "createSocketServer : %s \n", strerror(errno));
#endif
        fprintf(stdout, "bind faild!!\n");
        closeSockfd(sockfd);
        return 0;
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
    if(err < 0)
    {
#ifdef Debug
        fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
        fprintf(stdout, "listen faild!!\n");
        closeSockfd(serverSocketfd);
        return;
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

//文件服务器监听
void fileServerListen(int fileServerSockfd)
{
    //epoll
    //epoll_event结构体，用来创建和接收epoll事件
    struct epoll_event ev, events[MAX_LISTEN];
    //创建epoll fd
    int epfd = epoll_create(MAX_LISTEN + 1);

    ev.data.fd = fileServerSockfd;
    ev.events = EPOLLIN;

    //注册epoll事件
    epoll_ctl(epfd, EPOLL_CTL_ADD, fileServerSockfd, &ev);

    //监听
    int err = listen(fileServerSockfd, MAX_LISTEN);
    if(err < 0)
    {
#ifdef Debug
        fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
        fprintf(stdout, "listen faild!!\n");
        closeSockfd(fileServerSockfd);
        return;
    }

#ifdef Debug
    fprintf(stdout, "Max Listen : %d \n", MAX_LISTEN);
#endif

    extern ThreadPool *m_pThreadPool;
    TaskQueue *taskQueue = NULL;

    char recvBuf[2048 + 1];
    memset(recvBuf, 0, 1024);

    //一次事件的总数
    int numberFds = 0;
    int i = 0;
    int ret = 0;
    int clientfd = 0;
    Msg *msg = NULL, *sendMsg = NULL;
    while(1)
    {
        //等待
        numberFds = epoll_wait(epfd, events, MAX_LISTEN, EPOLL_TIME_OUT);

        //处理EPOLL_TIME_OUT内发生的所有事件
        for(i = 0; i < numberFds; ++i)
        {
            if (events[i].data.fd == fileServerSockfd)
            {
                //新连接
                newConnection(events[i].data.fd, epfd, &ev);
            }
            else if (events[i].events & EPOLLIN)
            {
                clientfd = events[i].data.fd;
                memset(recvBuf, 0, 2048);

                while(1)
                {
                    //收到消息
                    ret = recv(clientfd, recvBuf, 2048, 0);

                    if(ret > 0)
                    {
                        break;
                    }
                    else
                    {
                        if(errno == EAGAIN)
                        {
                            //这次没有数据了，下次再来
                            continue;
                        }
                        else
                        {
#ifdef Debug
                            fprintf(stderr, "recv : %s \n", strerror(errno));
#endif
                            ev.data.fd = clientfd;
                            epoll_ctl(epfd, EPOLL_CTL_DEL, clientfd, &ev);
                            closeSockfd(clientfd);
                            break;
                        }
                    }
                }

                if(ret < 0)
                {
                    break;
                }

                recvBuf[ret] = 0;

                msg = (Msg *)recvBuf;
                sendMsg = (Msg *)malloc(sizeof(Msg) + msg->m_iMsgLen);
                memcpy(sendMsg, recvBuf, ret);

                setblocking(clientfd);

                if (msg->m_eMsgType == Put_Upload)
                {
                    //上传
                    taskQueue = (pTaskQueue)malloc(sizeof(TaskQueue));
                    memset(taskQueue, 0, sizeof(TaskQueue));

                    taskQueue->p_fCallBackFunction = &uploadFileThread;
                    taskQueue->sockfd = clientfd;
                    taskQueue->p_vArg = (void *)sendMsg;
                    addJobThreadPool(m_pThreadPool, taskQueue);
                }
                else if(msg->m_eMsgType == Get_Download)
                {
                    //下载
                    taskQueue = (pTaskQueue)malloc(sizeof(TaskQueue));
                    memset(taskQueue, 0, sizeof(TaskQueue));

                    taskQueue->p_fCallBackFunction = &downloadFileThread;
                    taskQueue->sockfd = clientfd;
                    taskQueue->p_vArg = (void *)sendMsg;
                    addJobThreadPool(m_pThreadPool, taskQueue);
                }
                else
                {
                    closeSockfd(clientfd);
                }

                //删除这个fd
                ev.data.fd = clientfd;
                epoll_ctl(epfd, EPOLL_CTL_DEL, clientfd, &ev);
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
    ev->events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, clientSocketfd, ev);
}

/**
 * 收到socket消息
 * @param socketfd 客户端描述字
 */
void recvConnectionMsg(int socketfd, int epfd, struct epoll_event *ev)
{
    Msg *msg = NULL, *sendMsg = NULL;

    //接收缓存
    char *recvBuf = (char *)malloc((2 * RECV_BUF_MAX_SIZE + 1) * sizeof(char));
    memset(recvBuf, 0, 2 * RECV_BUF_MAX_SIZE * sizeof(char));

    //recvBuf尾部指针，用于接收数据
    char *pRearBuf = recvBuf;
    //recvBuf头部指针，用于传递数据
    char *pHeadBuf = recvBuf;
    //实际接收到得字节数量
    int recvRet = 0;
    //消息长度
    int msgLen = 0;
    int clientSocketfd = socketfd;
    int msgStructLen = sizeof(Msg);

    //发送的数据包不会超过RECV_BUF_MAX_SIZE
    //如果超过RECV_BUF_MAX_SIZE可能出现了TCP
    //粘包现象
    while(recvRet = recv(clientSocketfd, pRearBuf, RECV_BUF_MAX_SIZE, 0))
    {
        //读数据错误
        if(recvRet < 0)
        {
            if(errno == EAGAIN)
            {
                //这次没有数据了，下次再来
                break;
            }
            else
            {
#ifdef Debug
                fprintf(stderr, "recv : %s \n", strerror(errno));
#endif
                ev->data.fd = clientSocketfd;
                epoll_ctl(epfd, EPOLL_CTL_DEL, clientSocketfd, ev);
                closeSockfd(clientSocketfd);
                break;
            }
        }

        msgLen += recvRet;

        if (msgLen > 2 * RECV_BUF_MAX_SIZE)
        {
            //消息长度大于缓存长度
            exit(-1);
        }

        //接收到总数据已经大于了RECV_BUF_MAX_SIZE
        //为了安全做一定处理
        if(msgLen > RECV_BUF_MAX_SIZE)
        {
            unsigned char crc[5];
            memset(crc, 0xAF, 4);
            //在收到得buf中查找0xAFAFAFAF标志位
            void *findMove = memstr(pHeadBuf, (memlen_t)msgLen, (void *)crc);

            if(findMove)
            {
                int move = (char *)findMove - recvBuf;
                msgLen -= move;
                memcpy(recvBuf, findMove, msgLen);
                pHeadBuf = recvBuf;
                pRearBuf += msgLen;
            }
            else
            {
                ErrorMsg errorMsg;
                errorMsg.m_eErrorType = DataPackError;
                sendAckErrorMsg(clientSocketfd, errorMsg);
                break;
            }
        }

        //如果收到包长度小于结构体长度，暂定为丢弃
        //实际可能会出现拆包情况，收到小于包长度得
        //数据包
        if(msgLen < msgStructLen)
        {
            //指正移到缓存后
            pRearBuf += msgLen;
            continue;
        }

        recvBuf[msgLen] = '\0';

        //暂时没有想到好的解决方法
        //当且仅当发生TCP粘包时会执行这个loop
        //其它情况都无视这个loop
        stickyPackageLoop:

        //翻译buf
        msg = (Msg *)pHeadBuf;

        //校验位是否正确，如果正确则执行下一步
        if(msg->m_uiCheckCrc != (unsigned int)0xAFAFAFAF)
        {
            //矫正
            //尽量校正，校正成功则继续
            //否则continue，直到这个数据包被放弃
            unsigned char crc[5];
            memset(crc, 0xAF, 4);
            //在收到得buf中查找0xAFAFAFAF标志位
            void *findMove = memstr(pHeadBuf, msgLen, (void *)crc);

            if(findMove)
            {
                //找到标志位
                pHeadBuf = (char *)findMove;
                msgLen -= (pRearBuf - pHeadBuf);

                //重新翻译buf
                msg = (Msg *)pHeadBuf;
            }
            else
            {
                //没有找到标志位
                continue;
            }
        }

        //一个错误得包
        if(msg->m_iMsgLen > RECV_BUF_MAX_SIZE - msgStructLen || msg->m_iMsgLen < 0)
        {
            ErrorMsg errorMsg;
            errorMsg.m_eErrorType = DataPackError;
            sendAckErrorMsg(clientSocketfd, errorMsg);
            break;
        }

        if(msgLen < msgStructLen + msg->m_iMsgLen)
        {
            //拆包
            pRearBuf += msgLen;
            continue;
        }

        //投递数据包
        //现在消息是异步的，所以需要malloc一段空间用来存放msg消息
        sendMsg = (Msg *)malloc(msgStructLen + msg->m_iMsgLen);
        memcpy(sendMsg, msg, msgStructLen + msg->m_iMsgLen);
        recvMsg(clientSocketfd, sendMsg);
        sendMsg = NULL;
        msgLen -= msgStructLen + msg->m_iMsgLen;

        if(msgLen > 0)
        {
            //黏包
            pHeadBuf = pHeadBuf + msgStructLen + msg->m_iMsgLen;
            goto stickyPackageLoop;
        }

        //一轮结束pRearBuf和pHeadBuf指针重新指向recvBuf
        pRearBuf = recvBuf;
        pHeadBuf = recvBuf;
    }

    free(recvBuf);
}
