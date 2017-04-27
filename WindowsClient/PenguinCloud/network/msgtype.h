#ifndef MSGTYPE_H
#define MSGTYPE_H

//消息类型
typedef enum _MsgType{
    Ack_OK = 0,         //确定成功
    Ack_Error,          //确定错误
    Ack_Ready,          //准备就绪
    Put_Login,          //登录消息
    Get_FileLists,      //文件列表
    Get_Preview,        //预览响应
    Get_Download,       //文件下载
    Put_Move,           //移动操作
    Put_Copy,           //复制操作
    Put_NewFolder,      //新建文件夹
    Put_Rename,         //重命名
    Put_Upload,         //上传操作
    Put_Delete,         //删除操作
    Put_Share,          //分享操作
    Ack_Exit,           //退出
    Put_Register,       //注册请求
    Get_Register,       //注册响应
    Put_Preview,        //预览请求
    Put_TypeFile,
    Get_TypeFile        //获取指定类型的文件
}MsgType;

typedef enum _ResponeStatus
{
    Success = 0,
    Failed
}ResponeStatus;

//错误类型
typedef enum _ErrorType{
    DataPackError = 0,        //错误得数据包
    RenameError               //重命名错误
}ErrorType;

//预览文件类型结构
typedef enum _FileType{
    Office = 0,          // office文档
    Music,               // 音乐
    Video,               // 视频
    Image,               // 图片
    Pdf                  // PDF文档
    // ...               // 压缩文件
}FileType;

//文件类型， 针对ListView
typedef enum _TreeFileType {
        ALL = 0,
        DOCUMENT = 1,           //文档
        MUSIC,                  //音乐
        VIDEO,                  //视频
        IMAGE                   //图片
}TreeFileType;


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
#define LOGIN_FAILED -1
//#define LOGIN_FAILED_PASSWD -1
//#define LOGIN_FAILED_USERNAME -2
//登录消息结构
typedef struct _LoginMsg{
    int m_iLoginStatus;         //登录状态
    char m_aUserName[11];       //用户名
    char m_aUserPass[17];       //登录密码
}LoginMsg, *pLoginMsg;

#define MAX_PATH 1024
#define MAX_JSON_SIZE 1024
//文件列表消息结构
typedef struct _FileListsMsg{
    char m_aFolderPath[MAX_PATH + 1];
    char m_jsonFileList[MAX_JSON_SIZE + 1];
}FileListsMsg, *pFileListsMsg;

//下载信息消息结构
typedef struct _DownloadMsg{
    char serverFileIP[16];                  //文件服务器地址
    unsigned short serverFilePort;          //文件服务器端口
    long long m_llCurrentSize;              //当前传输进度
    char fileName[MAX_PATH + 1];            //文件名
}DownloadMsg, *pDownloadMsg;

//移动消息结构
typedef struct _MoveMsg{
    char sourcePath[MAX_PATH + 1];          // 源路径
    char DestinationPath[MAX_PATH + 1];    //目的地址
}MoveMsg, *pMoveMsg;
//复制消息结构
typedef struct _CopyMsg{
    char sourcePath[MAX_PATH + 1];          // 源路径
    char DestinationPath[MAX_PATH + 1];    //目的地址
}CopyMsg, *pCopyMsg;
//新建文件夹消息结构
typedef struct _NewFolderMsg{
    char folderName[MAX_PATH + 1]; // 新建文件的路径（包括文件夹名）
}NewFolderMsg, *pNewFolderMsg;

//上传操作消息结构
typedef struct _UploadMsg{
    char serverFileIP[16];                  //文件服务器地址
    unsigned short serverFilePort;          //文件服务器端口
    long long m_llCurrentSize;              //当前传输进度
    char fileName[MAX_PATH + 1];            //文件名
}UploadMsg, *pUploadMsg;

//删除操作消息结构
typedef struct _DeleteMsg{
    char path[MAX_PATH+1];
}DeleteMsg, *pDeleteMsg;

//分享操作消息结构
typedef struct _ShareMsg{

}ShareMsg, *pShareMsg;

//退出消息结构
typedef struct _ExitMsg{

}ExitMsg, *pExitMsg;

//重命名消息结构
typedef struct _RenameMsg{
    char newName[MAX_PATH + 1]; // 重命名文件(文件夹)
    char oldName[MAX_PATH + 1]; //old name
}RenameMsg, *pRenameMsg;


//注册消息结构
typedef struct _RegisterMsg{
    char username[64];      // 用户名
    char password[128];     // 密码
    // 保留段
    // 包括用户基本信息
}RegisterMsg, *pRegisterMsg;

//reponse client message
typedef struct _RegisterStatus{
        int status; // 0 success; 1 error;
}RegisterStatus;

//预览请求
typedef struct _PreviewMsg{
        FileType fileType;      //  请求的文件类型
        char filepath[1024];    //  文件路径
}PreviewMsg, *pPreviewMsg;
//返回预览信息
typedef struct _PreviewStatus{
    ResponeStatus status;
    FileType filetype;
}PreviewStatus, *pPreviewStatus;

//申请的文件列表类型
typedef struct _FileTypeListMsg {
    char username[64];
    TreeFileType filetype;
}FileTypeListMsg;
//响应
typedef struct _FileTypeListResponse {
        char json[2048];
}FileTypeListResponse;

#endif // MSGTYPE_H
