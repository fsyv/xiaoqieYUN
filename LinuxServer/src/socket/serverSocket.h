#ifndef SOCKET_SERVERSOCKET
#define SOCKET_SERVERSOCKET
/**
 * serverSocket
 * 创建服务端socket
 * 创建用户线程
 * @date 2017年 3月 14日
 * @version 1.0
 */
#define EPOLL_TIME_OUT 500

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

#endif //SOCKET_SERVERSOCKET
