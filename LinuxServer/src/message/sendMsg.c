#include "sendMsg.h"

#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>

//确定成功消息
int sendAckOkMsg(int sockfd)
{
    Msg msg;
    bzero(&msg, sizeof(Msg));

    msg.m_eMsgType = Ack_OK;
    msg.m_iMsgLen = 0;

    return sendMsg(sockfd, &msg);
}

//确定失败消息
int sendAckErrorMsg(int sockfd, ErrorMsg errorMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(ErrorMsg));
    bzero(msg, sizeof(Msg) + sizeof(ErrorMsg));

    msg->m_eMsgType = Ack_Error;
    msg->m_iMsgLen = sizeof(ErrorMsg);
    memcpy(msg->m_aMsgData, (void *)&errorMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}

//准备就绪消息
int sendReadyMsg(int sockfd)
{
    Msg msg;
    bzero(&msg, sizeof(Msg));

    msg.m_eMsgType = Ack_Ready;
    msg.m_iMsgLen = 0;

    return sendMsg(sockfd, &msg);
}
//登录消息
int sendLoginMsg(int sockfd, LoginMsg loginMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(LoginMsg));
    bzero(msg, sizeof(Msg) + sizeof(LoginMsg));

    msg->m_eMsgType = Put_Login;
    msg->m_iMsgLen = sizeof(LoginMsg);
    memcpy(msg->m_aMsgData, (void *)&loginMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}
//文件列表消息
int sendFileListMsg(int sockfd, FileListsMsg fileListsMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(FileListsMsg));
    bzero(msg, sizeof(Msg) + sizeof(FileListsMsg));

    msg->m_eMsgType = Get_FileLists;
    msg->m_iMsgLen = sizeof(FileListsMsg);
    memcpy(msg->m_aMsgData, (void *)&fileListsMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}
//预览信息消息
int sendPreviewMsg(int sockfd, PreviewMsg previewMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(PreviewMsg));
    bzero(msg, sizeof(Msg) + sizeof(PreviewMsg));

    msg->m_eMsgType = Get_Preview;
    msg->m_iMsgLen = sizeof(PreviewMsg);
    memcpy(msg->m_aMsgData, (void *)&previewMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}
//下载信息消息
int sendDownloadMsg(int sockfd, DownloadMsg downloadMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(DownloadMsg));
    bzero(msg, sizeof(Msg) + sizeof(DownloadMsg));

    msg->m_eMsgType = Get_Download;
    msg->m_iMsgLen = sizeof(DownloadMsg);
    memcpy(msg->m_aMsgData, (void *)&downloadMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}
//移动消息
int sendMoveMsg(int sockfd, MoveMsg moveMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(MoveMsg));
    bzero(msg, sizeof(Msg) + sizeof(MoveMsg));

    msg->m_eMsgType = Put_Move;
    msg->m_iMsgLen = sizeof(MoveMsg);
    memcpy(msg->m_aMsgData, (void *)&moveMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}
//新建文件夹消息
int sendNewFolderMsg(int sockfd, NewFolderMsg newFolderMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(NewFolderMsg));
    bzero(msg, sizeof(Msg) + sizeof(NewFolderMsg));

    msg->m_eMsgType = Put_NewFolder;
    msg->m_iMsgLen = sizeof(NewFolderMsg);
    memcpy(msg->m_aMsgData, (void *)&newFolderMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}
//上传操作消息
int sendUploadMsg(int sockfd, UploadMsg uploadMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(UploadMsg));
    bzero(msg, sizeof(Msg) + sizeof(UploadMsg));

    msg->m_eMsgType = Put_Upload;
    msg->m_iMsgLen = sizeof(UploadMsg);
    memcpy(msg->m_aMsgData, (void *)&uploadMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}
//删除操作消息
int sendDeleteMsg(int sockfd, DeleteMsg deleteMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(DeleteMsg));
    bzero(msg, sizeof(Msg) + sizeof(DeleteMsg));

    msg->m_eMsgType = Put_Delete;
    msg->m_iMsgLen = sizeof(DeleteMsg);
    memcpy(msg->m_aMsgData, (void *)&deleteMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}
//分享操作消息
int sendShareMsg(int sockfd, ShareMsg shareMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(ShareMsg));
    bzero(msg, sizeof(Msg) + sizeof(ShareMsg));

    msg->m_eMsgType = Put_Share;
    msg->m_iMsgLen = sizeof(ShareMsg);
    memcpy(msg->m_aMsgData, (void *)&shareMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}
//退出消息
int sendExitMsg(int sockfd, ExitMsg exitMsg)
{
    Msg *msg = (Msg *)malloc(sizeof(Msg) + sizeof(ExitMsg));
    bzero(msg, sizeof(Msg) + sizeof(ExitMsg));

    msg->m_eMsgType = Ack_Exit;
    msg->m_iMsgLen = sizeof(ExitMsg);
    memcpy(msg->m_aMsgData, (void *)&exitMsg, msg->m_iMsgLen);

    int ret = sendMsg(sockfd, msg);

    free(msg);
    return ret;
}

//RegisterStatus
int sendRegisterMsg(int sockfd, RegisterStatus status)
{
	Msg *msg = (Msg*)malloc(sizeof(Msg) + sizeof(RegisterStatus));
	bzero(msg, sizeof(Msg)+sizeof(RegisterStatus));

	msg->m_eMsgType = Get_Register;
	msg->m_iMsgLen = sizeof(RegisterStatus);
	memcpy(msg->m_aMsgData, (void *)&status, msg->m_iMsgLen);

        int ret = sendMsg(sockfd, msg);

        free(msg);
	return ret;

}


//发送消息
int sendMsg(int sockfd, Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    return send(sockfd, (void *)msg, sizeof(Msg) + msg->m_iMsgLen, 0);
}


