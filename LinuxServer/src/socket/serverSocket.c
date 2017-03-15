
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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
    serverAddress.sin_port = htonl(SERVER_PORT);

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
    while(1)
    {
        clientSocketfd = accept(serverSocketfd, (struct sockaddr *)&clientAddress, &clientAddressLen);
        if(clientSocketfd < 0)
        {
#ifdef Debug
            fprintf(stderr, "listenClient : %s \n", strerror(errno));
#endif
            fprintf(stdout, "listen faild!!\n");
            continue;
        }

        //加入队列
    }

}


