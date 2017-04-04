#include "serverOperating.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
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
void *uploadFileThread(void *arg)
{
    UploadMsg *uploadMsg = (UploadMsg *)arg;
    printf("fileName %s\n", uploadMsg->fileName);
}
