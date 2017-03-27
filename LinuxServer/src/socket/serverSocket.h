#ifndef SOCKET_SERVERSOCKET
#define SOCKET_SERVERSOCKET
/**
 * serverSocket
 * 创建服务端socket
 * 创建用户线程
 * @date 2017年 3月 14日
 * @version 1.0
 */

#include <sys/epoll.h>

#define SERVER_PORT 36975
#define EPOLL_TIME_OUT 500

//接收Buf最大缓存
#define RECV_BUF_MAX_SIZE 64 * 1024

//关闭服务端socketfd
void closeServersocketfd(int serverSocketfd);
//定时从队列中取用户队列
void *queueThread(void *arg);
//设置socket为非拥塞
void setnblocking(int sockfd);
//创建服务器socket
int createSocketServer();
//监听socket然后创建用户线程
void listenClient(int serverSocketfd);
//服务器监听到新的Tcp socket请求
void newConnection(int socketfd, int epfd, struct epoll_event *ev);
//给新连接发送一个应答
void sendReplyMessage(int socketfd, int epfd, struct epoll_event *ev);
//还没入队得新连接收到确定连接得消息
void recvNewConnectionMsg(int socketfd, int epfd, struct epoll_event *ev);
//用户线程
void *userThread(void *arg);

#endif //SOCKET_SERVERSOCKET
