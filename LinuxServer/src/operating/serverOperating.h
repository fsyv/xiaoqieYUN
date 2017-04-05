#ifndef LINUXSERVER_OPERATING_SERVEROPERATING_H
#define LINUXSERVER_OPERATING_SERVEROPERATING_H

//获取目录下的文件
char *getDirFileLists(char *userDir);
//文件上传的线程
void *uploadFileThread(void *arg);

#endif //LINUXSERVER_OPERATING_SERVEROPERATING_H
