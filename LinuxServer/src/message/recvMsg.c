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
        case Put_NewFolder:
#ifdef Debug
            fprintf(stdout, "Put_NewFolder\n");
#endif
            //新建文件夹
            recvNewFolderMsg(sockfd, msg);
            break;
        case Get_Download:
#ifdef Debug
            fprintf(stdout, "Get_Download\n");
#endif
            recvDownloadMsg(sockfd, msg);
            break;

        case Put_Delete:
#ifdef Debug
            fprintf(stdout, "Put_Delete\n");
#endif
            recvDeleteMsg(sockfd, msg);
            break;

        case Put_Rename:
#ifdef Debug
            fprintf(stdout, "Put_Rename\n");
#endif
            recvRenameMsg(sockfd, msg);
            break;

        case Put_Move:
#ifdef Debug
            fprintf(stdout, "Put_Move\n");
#endif
            recvMoveMsg(sockfd, msg);
            break;
        case Put_Copy:
#ifdef Debug
            fprintf(stdout, "Put_Copy\n");
#endif
            recvCopyMsg(sockfd, msg);
            break;
    	case Put_Register:
//#ifdef Debug
	    fprintf(stdout, "Put_Register\n");
//#endif
	    recvRegisterMsg(sockfd, msg);
	    break;
	case Put_Preview:
//#ifdef Debug
		fprintf(stdout, "Put_Preview\n");
//#endif
		recvPreviewMsg(sockfd, msg);
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
    int ret;
    LoginMsg loginMsg;
    memset(&loginMsg, 0, sizeof(LoginMsg));

    printf("LOGIN_SUCCESS\n");

    memcpy(&loginMsg, msg->m_aMsgData, msg->m_iMsgLen);
    printf("%s %s\n", loginMsg.m_aUserName, loginMsg.m_aUserPass);
    ret = login(loginMsg.m_aUserName, loginMsg.m_aUserPass);

    printf("%d\n", ret);
    if (ret == MYSQL_LOGIN_SUCCESS)
        loginMsg.m_iLoginStatus = LOGIN_SUCCESS;
    else
	loginMsg.m_iLoginStatus = LOGIN_FAILED;
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

//下载消息
void recvDownloadMsg(int sockfd, Msg *msg)
{
    DownloadMsg downloadMsg;
    memset(&downloadMsg, 0, sizeof(UploadMsg));

    memcpy(&downloadMsg, msg->m_aMsgData, msg->m_iMsgLen);

    //告诉客户端在哪儿下
    downloadMsg.serverFilePort = 36976;

    sendDownloadMsg(sockfd, downloadMsg);
}
//上传操作消息
void recvUploadMsg(int sockfd, Msg *msg)
{
    UploadMsg uploadMsg;
    memset(&uploadMsg, 0, sizeof(UploadMsg));

    memcpy(&uploadMsg, msg->m_aMsgData, msg->m_iMsgLen);

    //告诉客户端往哪儿传
    uploadMsg.serverFilePort = 36976;

    sendUploadMsg(sockfd, uploadMsg);
}

//新建文件夹消息
void recvNewFolderMsg(int sockfd, Msg *msg)
{
    int ret;
    NewFolderMsg newFolderMsg;
    memset(&newFolderMsg, 0, sizeof(NewFolderMsg));
    memcpy(&newFolderMsg, msg->m_aMsgData, msg->m_iMsgLen);

    ret = createNewFolder(newFolderMsg.folderName);
    if(ret == 0)
    {
        //donothing
    }
    else
    {
        ErrorMsg errorMsg;
        errorMsg.m_eErrorType = CreateFolderFailed;
        sendAckErrorMsg(sockfd, errorMsg);
    }
}

//删除操作消息
void recvDeleteMsg(int sockfd, Msg *msg)
{
    DeleteMsg deleteMsg;
    memset(&deleteMsg, 0, sizeof(DeleteMsg));
    memcpy(&deleteMsg, msg->m_aMsgData, msg->m_iMsgLen);

    if(removeFolder(deleteMsg.path) == -1)
    {
        //错误处理
    }
}

//重命名消息
void recvRenameMsg(int sockfd, Msg *msg)
{
    int ret;
    RenameMsg renameMsg;
    memset(&renameMsg, 0, sizeof(RenameMsg));
    memcpy(&renameMsg, msg->m_aMsgData, msg->m_iMsgLen);

    ret = renameFileOrFolder(renameMsg.oldName, renameMsg.newName);
    
    printf("sendRenameError\n");

    if(ret == -1)
    {
        printf("rename error\n");
        ErrorMsg msg;
        memset(&msg, 0, sizeof(ErrorMsg));
        msg.m_eErrorType = RenameError;
        sendAckErrorMsg(sockfd, msg);
        //错误处理
    }
    else
    {
        //返回成功
    }


}

//移动消息
void recvMoveMsg(int sockfd, Msg *msg)
{
    int ret;

    MoveMsg moveMsg;
    memset(&moveMsg, 0, sizeof(MoveMsg));
    memcpy(&moveMsg, msg->m_aMsgData, msg->m_iMsgLen);

    ret = moveSrcToDes(moveMsg.sourcePath, moveMsg.DestinationPath);

    if(ret == -1)
    {
        //错误处理
    }
}

//复制消息
void recvCopyMsg(int sockfd, Msg *msg)
{
    int ret;

    CopyMsg copyMsg;
    memset(&copyMsg, 0, sizeof(MoveMsg));
    memcpy(&copyMsg, msg->m_aMsgData, msg->m_iMsgLen);

    ret = copySrcToDes(copyMsg.sourcePath, copyMsg.DestinationPath);

    if(ret == -1)
    {
        //错误处理
    }
}

void recvRegisterMsg(int sockfd, Msg *msg)
{
    	int ret;
	char path[1024] = "/var/penguin/";
	RegisterMsg registerMsg;
	memset(&registerMsg, 0, sizeof(RegisterMsg));
	memcpy(&registerMsg, msg->m_aMsgData, msg->m_iMsgLen);

	ret = registerUser(registerMsg.username, registerMsg.password);

	RegisterStatus rs;
	
	if (ret == 0)
	{
		//success
		memset(&rs, 0, sizeof(RegisterStatus));
		rs.status = 0;
		strcat(path, registerMsg.username);
		mkdir(path);	
	}
    	else if (ret == -1)
	{
		memset(&rs, 0, sizeof(RegisterStatus));
                rs.status = 1;
	}
	sendRegisterMsg(sockfd, rs);
	
	printf("send Register Status\n");
}

void recvPreviewMsg(int sockfd, Msg *msg)
{
	int ret;

	PreviewMsg previewMsg;
	memset(&previewMsg, 0, sizeof(PreviewMsg));
	memcpy(&previewMsg, msg->m_aMsgData, msg->m_iMsgLen);
	
	switch(previewMsg.fileType)
	{
	case Office:
		// success return 1, else return -1
		printf("start convert\n");
		convertOfficeToPdf(sockfd, previewMsg.filepath);
		break;
	case Music:
		break;

	case Video:
		break;
	case Image:
		break;

	}
}

