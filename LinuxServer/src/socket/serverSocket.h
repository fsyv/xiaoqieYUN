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
#define FILE_SERVER_PORT 36976
#define EPOLL_TIME_OUT 500

//接收Buf最大缓存
#define RECV_BUF_MAX_SIZE 64 * 1024

#define MAX_LISTEN 64 * 1024

//创建响应服务器
void createServerService();
//创建文件服务器
void *createFileServer(void *arg);
//关闭服务端socketfd
void closeSockfd(int sockfd);
//设置socket为非拥塞
void setnblocking(int sockfd);
//设置socket为拥塞
void setblocking(int sockfd);
//创建socket
int createSocketServer(unsigned int port);
//监听socket然后创建用户线程
void listenClient(int serverSocketfd);
//文件服务器监听
void fileServerListen(int fileServerSockfd);
//服务器监听到新的Tcp socket请求
void newConnection(int socketfd, int epfd, struct epoll_event *ev);
//收到socket消息
void recvConnectionMsg(int socketfd, int epfd, struct epoll_event *ev);

#endif //SOCKET_SERVERSOCKET
