#include "recvMsg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../operating/serverOperating.h"
#include "../queue/threadPool.h"

/**
 * 收到消息
 * @param sockfd
 * @param msg
 * @param arg 传参
 * @return
 */
void recvMsg(int sockfd, Msg *msg)
{
    switch (msg->m_eMsgType){
        case Ack_OK:
#ifdef Debug
            fprintf(stdout, "Ack_OK\n");
#endif
            //确定成功
            break;
        case Ack_Error:
#ifdef Debug
            fprintf(stdout, "Ack_Error\n");
#endif
            //确定错误
            break;
        case Ack_Ready:
#ifdef Debug
            fprintf(stdout, "Ack_Ready\n");
#endif
            //准备就绪
            recvReadyMsg(sockfd, msg);
            break;
        case Put_Login:
#ifdef Debug
            fprintf(stdout, "Put_Login\n");
#endif
            //登录消息
            recvLoginMsg(sockfd, msg);
            break;
        case Get_FileLists:
#ifdef Debug
            fprintf(stdout, "Get_FileLists\n");
#endif
            //文件列表
            recvFileListMsg(sockfd, msg);
            break;
        case Put_Upload:
#ifdef Debug
            fprintf(stdout, "Put_Upload\n");
#endif
            //上传文件
            recvUploadMsg(sockfd, msg);
            break;
    }
}

/**
 * 收到准备就绪消息
 * @param sockfd 消息得句柄
 * @param msg 消息结构体
 * @return
 */
void recvReadyMsg(int sockfd, Msg *msg)
{
    ReadyMsg readyMsg;
    memcpy(&readyMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

/**
 * 登录消息
 * @param sockfd
 * @param msg
 */
void recvLoginMsg(int sockfd, Msg *msg)
{
    LoginMsg loginMsg;
    memset(&loginMsg, 0, sizeof(LoginMsg));

    memcpy(&loginMsg, msg->m_aMsgData, msg->m_iMsgLen);
    loginMsg.m_iLoginStatus = LOGIN_SUCCESS;
    sendLoginMsg(sockfd, loginMsg);
}

//文件列表消息
void recvFileListMsg(int sockfd, Msg *msg)
{
    FileListsMsg fileListsMsg;
    memset(&fileListsMsg, 0, sizeof(FileListsMsg));

    memcpy(&fileListsMsg, msg->m_aMsgData, msg->m_iMsgLen);

    char *fileListsJson = getDirFileLists(fileListsMsg.m_aFolderPath);

    if(fileListsJson)
    {
        strcpy(fileListsMsg.m_jsonFileList, fileListsJson);
        sendFileListMsg(sockfd, fileListsMsg);
        free(fileListsJson);
    }
    else
    {
        ErrorMsg errorMsg;
        errorMsg.m_eErrorType = NoSuchFileOrDirectory;
        sendAckErrorMsg(sockfd, errorMsg);
    }
}

//上传操作消息
void recvUploadMsg(int sockfd, Msg *msg)
{
    UploadMsg *uploadMsg = (UploadMsg *)malloc(sizeof(UploadMsg));
    memset(uploadMsg, 0, sizeof(UploadMsg));

    memcpy(uploadMsg, msg->m_aMsgData, msg->m_iMsgLen);
    memcpy(uploadMsg->serverUrl, (void *)&sockfd, sizeof(int));

    extern ThreadPool *m_pThreadPool;
    addJobThreadPool(m_pThreadPool, uploadFileThread, (void *)uploadMsg);
}