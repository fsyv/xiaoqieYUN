#include "serverFileSocket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../message/nstdmsgio.h"
#include "../operating/serverOperating.h"
#include "../queue/threadPool.h"

//文件传输的socket
void *createServerFileSocket(void *arg)
{
    int err = 0;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
#ifdef Debug
        fprintf(stderr, "createServerFileSocket : %s \n", strerror(errno));
#endif
        fprintf(stdout, "createServerFileSocket faild!!\n");
        exit(-1);
    }

#ifdef Debug
    fprintf(stdout, "file server  created!!\n");
#endif

    struct sockaddr_in serverAddress;
    int serverAddressLen = sizeof(struct sockaddr_in);
    memset(&serverAddress, 0, serverAddressLen);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(SERVER_FILE_PORT);

#ifdef Debug
    fprintf(stdout, "file server Port at %d\n", SERVER_FILE_PORT);
#endif

    err = bind(sockfd, (struct sockaddr *)&serverAddress, serverAddressLen);
    if(err < 0)
    {
#ifdef Debug
        fprintf(stderr, "createSocketServer : %s \n", strerror(errno));
#endif
        fprintf(stdout, "file server bind faild!!\n");
        shutdown(sockfd, SHUT_RDWR);
        close(sockfd);
        exit(-1);
    }
#ifdef Debug
    fprintf(stdout, "file server bind  created!!\n");
#endif

    //监听
    err = listen(sockfd, MAX_LISTEN);
    if(err)
    {
#ifdef Debug
        fprintf(stderr, "file server listenClient : %s \n", strerror(errno));
#endif
        fprintf(stdout, "file server listen faild!!\n");
        shutdown(sockfd, SHUT_RDWR);
        close(sockfd);
        exit(-1);
    }

#ifdef Debug
    fprintf(stdout, "file server Max Listen : %d \n", MAX_LISTEN);
#endif

    int clientSocketfd = 0;
    int ret = 0;
    Msg *msg = NULL, *sendMsg = NULL;

    char recvBuf[1024];

    extern ThreadPool *m_pThreadPool;
    TaskQueue *taskQueue = NULL;

    while(clientSocketfd = accept(sockfd, NULL, NULL))
    {
        if(clientSocketfd < 0)
        {
#ifdef Debug
            fprintf(stderr, "file server accept : %s \n", strerror(errno));
#endif
            continue;
        }

        ret = recv(clientSocketfd, recvBuf, 1024, 0);

        if (ret < 0)
        {
#ifdef Debug
            fprintf(stderr, "file server recv : %s \n", strerror(errno));
#endif
            close(clientSocketfd);
            continue;
        }

        msg = (Msg *)recvBuf;
        sendMsg = (Msg *)malloc(sizeof(Msg) + msg->m_iMsgLen);
        memcpy(sendMsg, recvBuf, ret);

        if (msg->m_eMsgType == Put_Upload)
        {
            //上传
            taskQueue = (pTaskQueue)malloc(sizeof(TaskQueue));
            memset(taskQueue, 0, sizeof(TaskQueue));

            taskQueue->p_fCallBackFunction = &uploadFileThread;
            taskQueue->sockfd = clientSocketfd;
            taskQueue->p_vArg = (void *)sendMsg;
        }
        else if(msg->m_eMsgType == Get_Download)
        {
            //下载
            taskQueue = (pTaskQueue)malloc(sizeof(TaskQueue));
            memset(taskQueue, 0, sizeof(TaskQueue));

            taskQueue->p_fCallBackFunction = &downloadFileThread;
            taskQueue->sockfd = clientSocketfd;
            taskQueue->p_vArg = (void *)sendMsg;
        }
        else
        {
            continue;
        }
        addJobThreadPool(m_pThreadPool, taskQueue);
    }
}