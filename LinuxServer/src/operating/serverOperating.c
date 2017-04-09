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
#include <stdbool.h>
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

    UploadMsg uploadMsg;
    memset(&uploadMsg, 0, sizeof(UploadMsg));

    memcpy(&uploadMsg, msg->m_aMsgData, msg->m_iMsgLen);

    char file[1024] = "/var/penguin/";
    strcat(file, uploadMsg.fileName);

    printf("fileName %s\n", uploadMsg.fileName);
    printf("file %s\n", file);

    //二进制可写方式追加
    FILE *fp = fopen(file, "wb");

    if(fp == NULL)
    {
#ifdef Debug
        fprintf(stdout, "fopen %s\n", strerror(errno));
#endif
        return NULL;
    }

    long long currentFileSeek = lseek(fp, 0, SEEK_END);
    printf("currentFileSeek = %lld\n", currentFileSeek);

    char *recvBuf = (char *)malloc(MAX_RECV_BUF + 1);
    memset(recvBuf, 0, MAX_RECV_BUF);

    int ret = 0;

    //把当前文件服务器文件索引发送给客户端
    uploadMsg.m_llCurrentSize = currentFileSeek;
    sendUploadMsg(sockfd, uploadMsg);

    while((ret = recv(sockfd, recvBuf, MAX_RECV_BUF, 0)) > 0)
    {
        currentFileSeek += ret;
        printf("currentFileSeek = %lld\n", currentFileSeek);
        fwrite(recvBuf, sizeof(char), ret, fp);
        memset(recvBuf, 0, ret);
    }

    fclose(fp);
    free(recvBuf);
    return NULL;
}

//文件下载
void *downloadFileThread(int sockfd, void *arg)
{
    Msg *msg = (Msg *)arg;

    DownloadMsg downloadMsg;
    memset(&downloadMsg, 0, sizeof(DownloadMsg));

    memcpy(&downloadMsg, msg->m_aMsgData, msg->m_iMsgLen);

    char file[1024] = "/var/penguin/";
    strcat(file, downloadMsg.fileName);

    printf("fileName %s\n", downloadMsg.fileName);
    printf("file %s\n", file);

    //可写权限打开
    FILE *fp = fopen(file, "rb");
    if(fp == NULL)
    {
#ifdef Debug
        fprintf(stdout, "fopen %s\n", strerror(errno));
#endif
        return NULL;
    }

    long long currentFileSeek = lseek(fp, downloadMsg.m_llCurrentSize, SEEK_CUR);

    char *recvBuf = (char *)malloc(MAX_RECV_BUF + 1);
    memset(recvBuf, 0, MAX_RECV_BUF);

    int ret = 0;

    while(!feof(fp))
    {
        ret = fread(recvBuf, sizeof(char), MAX_RECV_BUF, fp);
        currentFileSeek += ret;
        printf("currentFileSeek = %d\n", currentFileSeek);
        send(sockfd, (void *)recvBuf, ret, 0);
        memset(recvBuf, 0, ret);
    }

    free(recvBuf);
    fclose(fp);
    close(sockfd);
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


/**
 *  删除操作  包括5个函数
 */

//判断是否为目录
bool is_dir(const char *path)
{
    struct stat statbuf;
    if(lstat(path, &statbuf) ==0)//lstat返回文件的信息，文件信息存放在stat结构中
    {
        return S_ISDIR(statbuf.st_mode) != 0;//S_ISDIR宏，判断文件类型是否为目录
    }
    return false;
}

//判断是否为常规文件
bool is_file(const char *path)
{
    struct stat statbuf;
    if(lstat(path, &statbuf) ==0)
        return S_ISREG(statbuf.st_mode) != 0;//判断文件是否为常规文件
    return false;
}

//判断是否是特殊目录
bool is_special_dir(const char *path)
{
    return strcmp(path, ".") == 0 || strcmp(path, "..") == 0;
}

//生成完整的文件路径
void get_file_path(const char *path, const char *file_name,  char *file_path)
{
    strcpy(file_path, path);
    if(file_path[strlen(path) - 1] != '/')
        strcat(file_path, "/");
    strcat(file_path, file_name);
}

//递归删除
int delete_file(const char *path)
{
    DIR *dir;
    struct dirent *dir_info;
    char file_path[PATH_MAX];
    if(is_file(path))
    {
        remove(path);
        return 0;
    }
    if(is_dir(path))
    {
        if((dir = opendir(path)) == NULL)
            return 0;
        while((dir_info = readdir(dir)) != NULL)
        {
            get_file_path(path, dir_info->d_name, file_path);
            if(is_special_dir(dir_info->d_name))
                continue;
            delete_file(file_path);
            rmdir(file_path);
        }
    }

    return rmdir(path);

}

//删除文件夹
int removeFolder(char *path)
{
    char sysDir[1024] = "/var/penguin/";
    strcat(sysDir, path);
    return delete_file(sysDir);
}


//重命名
int renameFileOrFolder(char *_oldpath, char *_newpath)
{
    char newpath[1024] = "/var/penguin/";
    char oldpath[1024] = "/var/penguin/";

    strcat(oldpath, _oldpath);
    strcat(newpath, _newpath);

    return rename(oldpath, newpath);
}

int moveSrcToDes(char *src, char *des)
{
    char srcPath[1024] = "/var/penguin/";
    char desPath[1024] = "/var/penguin/";
    char command[2048] = "mv ";

    strcat(srcPath, src);
    strcat(desPath, des);

    strcat(command, srcPath);
    strcat(command, " ");
    strcat(command, desPath);

    printf("%s\n", command);

    return system(command);
}


int copySrcToDes(char *src, char *des)
{
    char srcPath[1024] = "/var/penguin/";
    char desPath[1024] = "/var/penguin/";
    char command[2048] = "cp -r ";        //递归复制

    strcat(srcPath, src);
    strcat(desPath, des);

    strcat(command, srcPath);
    strcat(command, " ");
    strcat(command, desPath);

    printf("%s\n", command);

    return system(command);
}
