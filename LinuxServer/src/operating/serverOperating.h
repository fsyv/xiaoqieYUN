#ifndef LINUXSERVER_OPERATING_SERVEROPERATING_H
#define LINUXSERVER_OPERATING_SERVEROPERATING_H

#include "../message/nstdmsgio.h"
#include "../database/database.h"
#define MAX_RECV_BUF (64 * 1024)

//获取目录下的文件
char *getDirFileLists(char *userDir);
//文件上传的线程
void *uploadFileThread(int sockfd, void *arg);
//文件下载
void *downloadFileThread(int sockfd, void *arg);
//新建文件夹
int createNewFolder(char *folderPath);
//重命名
int renameFileOrFolder(char *oldpath, char *newpath);
//删除文件夹
int removeFolder(char *folderPath);
//移动文件或文件夹
int moveSrcToDes(char *src, char *des);
//复制文件或文件夹
int copySrcToDes(char *src, char *des);


//login
int loginUser(const char *username, const char *password);
//register
int registerUser(const char *username, const char *password);
//preview
int convertOfficeToPdf(int sockfd, const char *filename);
#endif //LINUXSERVER_OPERATING_SERVEROPERATING_H
