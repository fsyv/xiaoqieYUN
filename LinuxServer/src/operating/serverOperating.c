#include "serverOperating.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h> // mkdir
#include <dirent.h>

#include "../cjson/cJSON.h"
#include "../message/nstdmsgio.h"


/**
 * 获取目录下的文件
 * @param dir
 * @return
 */
char *getDirFileLists(char *userDir)
{
    char sysDir[1024] = "/var/penguin/";
    strcat(sysDir, userDir);

    printf("%s\n", sysDir);

    DIR *dir = NULL;
    struct dirent *child = NULL;
    struct stat statBuf;

    dir = opendir(sysDir);
    if(!dir)
    {
#ifdef Debug
        fprintf(stderr, "getDirFileLists : %s \n", strerror(errno));
#endif
        return NULL;
    }

    cJSON *pRoot = cJSON_CreateObject();
    cJSON *pArray = cJSON_CreateArray();
    cJSON_AddItemToObject(pRoot, userDir, pArray);

    cJSON *pItem = NULL;

    chdir(sysDir);

    while((child = readdir(dir)) != NULL)
    {
        lstat(child->d_name, &statBuf);

        if (S_ISDIR(statBuf.st_mode))
        {
            //目录
            if(strcmp(child->d_name,".")==0 || strcmp(child->d_name,"..")==0)
                continue;

            pItem = cJSON_CreateObject();
            cJSON_AddStringToObject(pItem, "name", child->d_name);
            cJSON_AddStringToObject(pItem, "type", "folder");
            cJSON_AddNumberToObject(pItem, "lastmodifytime", statBuf.st_mtim.tv_sec);
        }
        else if(S_ISREG(statBuf.st_mode))
        {
            //文件
            pItem = cJSON_CreateObject();
            cJSON_AddStringToObject(pItem, "name", child->d_name);
            cJSON_AddStringToObject(pItem, "type", "file");
            cJSON_AddNumberToObject(pItem, "lastmodifytime", statBuf.st_mtim.tv_sec);
            cJSON_AddNumberToObject(pItem, "size", statBuf.st_size);
        }
        cJSON_AddItemToArray(pArray, pItem);
    }

    chdir("-");
    closedir(dir);

#ifdef Debug
    fprintf(stdout, "%s\n", cJSON_Print(pRoot));
#endif

    char* szOut = cJSON_PrintUnformatted(pRoot);
    cJSON_Delete(pRoot);

    return szOut;
}

//文件上传的线程
void *uploadFileThread(int sockfd, void *arg)
{
    Msg *msg = (Msg *)arg;
    printf("uploadFileThread\n");

    UploadMsg uploadMsg;
    memset(&uploadMsg, 0, sizeof(UploadMsg));

    memcpy(&uploadMsg, msg->m_aMsgData, msg->m_iMsgLen);
    uploadMsg.m_iLoginStatus = 1;

    char file[1024] = "/var/penguin/";
    strcat(file, uploadMsg.uploadPath);
    strcat(file, uploadMsg.fileName);

    printf("uploadPath %s\n", uploadMsg.uploadPath);
    printf("fileName %s\n", uploadMsg.fileName);
    printf("file %s\n", file);

    //可写权限打开
    FILE *fp = fopen(file, "ab+");
    if(fp == NULL)
    {
#ifdef Debug
        fprintf(stdout, "fopen %s\n", strerror(errno));
#endif
        return NULL;
    }

    char *recvBuf = (char *)malloc(sizeof(char) * 64 * 1024);
    memset(recvBuf, 0, 64 * 1024);

    int ret = 0;

    printf("1\n");
    sendUploadMsg(sockfd, uploadMsg);
    while((ret = recv(sockfd, recvBuf, 64 * 1024, 0)) > 0)
    {
        printf("ret = %d\n", ret);
        fwrite(recvBuf, sizeof(char), ret, fp);
        memset(recvBuf, 0, 64 * 1024);
    }
    printf("2\n");
    close(fp);
    close(sockfd);
    free(recvBuf);
    return NULL;
}

//新建文件夹
// 失败返回-1 成功返回0
int createNewFolder(char *folderPath)
{
    //用户及用户组可读写
    char sysDir[1024] = "/var/penguin/";
    strcat(sysDir, folderPath);

    printf("%s\n", sysDir);

    return mkdir(sysDir,  S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP);
}
