#ifndef UPDATEFILEMSG_H
#define UPDATEFILEMSG_H

typedef struct _UpdateFileMsg{
    unsigned int m_uiCheckCrc;              //消息校验 0xAFAFAFAF
    unsigned long long m_ullFileSize;       //文件长度
    unsigned long long m_ullCurrentSize;    //当前长度
    int m_iMsgLen;							//消息长度
    char m_aMsgData[0];						//消息内容
}UpdateFileMsg, &pUpdateFileMsg;

#endif // UPDATEFILEMSG_H
