#ifndef LINUXSERVER_MESSAGE_SENDMSG_H
#define LINUXSERVER_MESSAGE_SENDMSG_H

#include "msg.h"
#include "msgType.h"

//确定成功消息
int sendAckOkMsg(int sockfd);
//确定失败消息
int sendAckErrorMsg(int sockfd, ErrorMsg errorMsg);
//准备就绪消息
int sendReadyMsg(int sockfd);
//登录消息
int sendLoginMsg(int sockfd, LoginMsg loginMsg);
//文件列表消息
int sendFileListMsg(int sockfd, FileListsMsg fileListsMsg);
//预览信息消息
int sendPreviewMsg(int sockfd, PreviewStatus status);
//下载信息消息
int sendDownloadMsg(int sockfd, DownloadMsg downloadMsg);
//移动消息
int sendMoveMsg(int sockfd, MoveMsg moveMsg);
//新建文件夹消息
int sendNewFolderMsg(int sockfd, NewFolderMsg newFolderMsg);
//上传操作消息
int sendUploadMsg(int sockfd, UploadMsg uploadMsg);
//删除操作消息
int sendDeleteMsg(int sockfd, DeleteMsg deleteMsg);
//分享操作消息
int sendShareMsg(int sockfd, ShareMsg shareMsg);
//退出消息
int sendExitMsg(int sockfd, ExitMsg exitMsg);
//send RegisterMsg
int sendRegisterMsg(int sockfd, RegisterStatus status);

//发送消息
int sendMsg(int sockfd, Msg *msg);

#endif //LINUXSERVER_MESSAGE_SENDMSG_H
