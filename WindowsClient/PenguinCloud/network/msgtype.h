#ifndef MSGTYPE_H
#define MSGTYPE_H

//消息类型
typedef enum _MsgType{
    Ack_OK = 0,         //确定成功
    Ack_Error,          //确定错误
    Ack_Ready,          //准备就绪
    Put_Login,          //登录消息
    Get_FileLists,      //文件列表
    Get_Preview,        //文件预览
    Get_Download,       //文件下载
    Put_Move,           //移动操作
    Put_NewFolder,      //新建文件夹
    Put_Upload,         //上传操作
    Put_Delete,         //删除操作
    Put_Share,          //分享操作
    Ack_Exit            //退出
}MsgType;

//错误类型
typedef enum _ErrorType{
    DataPackError = 0        //错误得数据包
}ErrorType;
//发生了错误
typedef struct _ErrorMsg{
    ErrorType m_eErrorType;
}ErrorMsg, *pErrorMsg;

//准备就绪得消息结构
typedef struct _ReadyMsg{
    int m_iClientSockfd;                 //客户端描述字
    unsigned int m_uiClientnaddress;     //客户端网络地址
}ReadyMsg, *pReadyMsg;


#define LOGIN_SUCCESS 1
#define PUT_LOGIN 0
#define LOGIN_FAILED_PASSWD -1
#define LOGIN_FAILED_USERNAME -2
//登录消息结构
typedef struct _LoginMsg{
    int m_iLoginStatus;         //登录状态
    char m_aUserName[10];       //用户名
    char m_aUserPass[16];       //登录密码
}LoginMsg, *pLoginMsg;

//文件列表消息结构
typedef struct _FileListsMsg{

}FileListsMsg, *pFileListsMsg;

//预览信息消息结构
typedef struct _PreviewMsg{

}PreviewMsg, *pPreviewMsg;

//下载信息消息结构
typedef struct _DownloadMsg{

}DownloadMsg, *pDownloadMsg;

//移动消息结构
typedef struct _MoveMsg{

}MoveMsg, *pMoveMsg;

//新建文件夹消息结构
typedef struct _NewFolderMsg{

}NewFolderMsg, *pNewFolderMsg;

//上传操作消息结构
typedef struct _UploadMsg{

}UploadMsg, *pUploadMsg;

//删除操作消息结构
typedef struct _DeleteMsg{

}DeleteMsg, *pDeleteMsg;

//分享操作消息结构
typedef struct _ShareMsg{

}ShareMsg, *pShareMsg;

//退出消息结构
typedef struct _ExitMsg{

}ExitMsg, *pExitMsg;

#endif // MSGTYPE_H
