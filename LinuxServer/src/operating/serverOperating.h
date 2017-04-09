#ifndef LINUXSERVER_OPERATING_SERVEROPERATING_H
#define LINUXSERVER_OPERATING_SERVEROPERATING_H

#include "../message/nstdmsgio.h"

#define MAX_RECV_BUF (64 * 1024)

//获取目录下的文件
char *getDirFileLists(char *userDir);
//文件上传的线程
void *uploadFileThread(int sockfd, void *arg);
//文件下载
void *downloadFileThread(int sockfd, void *arg);
//新建文件夹
int createNewFolder(char *folderPath);

//删除文件夹
int removeFolder(char *folderPath);
#endif //LINUXSERVER_OPERATING_SERVEROPERATING_H
