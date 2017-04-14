#include "abstractnetwork.h"

#include "string.h"

AbstractNetwork::AbstractNetwork(QObject *parent):
    QTcpSocket(parent)
{
    m_iMsgStructLen = sizeof(Msg);
}

AbstractNetwork::~AbstractNetwork()
{

}

int AbstractNetwork::sendAckOkMsg()
{
    Msg msg;

    memset(&msg, 0, m_iMsgStructLen);

    msg.m_eMsgType = Ack_OK;
    msg.m_iMsgLen = 0;

    return sendMsg(&msg);
}

int AbstractNetwork::sendAckErrorMsg(ErrorMsg errorMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(ErrorMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(ErrorMsg));

    msg->m_eMsgType = Ack_Error;
    msg->m_iMsgLen = sizeof(ErrorMsg);
    memcpy(msg->m_aMsgData, (void *)&errorMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendReadyMsg()
{
    Msg msg;

    memset(&msg, 0, m_iMsgStructLen);

    msg.m_eMsgType = Ack_Ready;
    msg.m_iMsgLen = 0;

    return sendMsg(&msg);
}

int AbstractNetwork::sendLoginMsg(LoginMsg loginMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(LoginMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(LoginMsg));

    msg->m_eMsgType = Put_Login;
    msg->m_iMsgLen = sizeof(LoginMsg);
    memcpy(msg->m_aMsgData, (void *)&loginMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendFileListMsg(FileListsMsg fileListsMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(FileListsMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(FileListsMsg));

    msg->m_eMsgType = Get_FileLists;
    msg->m_iMsgLen = sizeof(FileListsMsg);
    memcpy(msg->m_aMsgData, (void *)&fileListsMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendPreviewMsg(PreviewMsg previewMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(PreviewMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(PreviewMsg));

    msg->m_eMsgType = Put_Preview;
    msg->m_iMsgLen = sizeof(PreviewMsg);
    memcpy(msg->m_aMsgData, (void *)&previewMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendDownloadMsg(DownloadMsg downloadMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(DownloadMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(DownloadMsg));

    msg->m_eMsgType = Get_Download;
    msg->m_iMsgLen = sizeof(DownloadMsg);
    memcpy(msg->m_aMsgData, (void *)&downloadMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendMoveMsg(MoveMsg moveMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(MoveMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(MoveMsg));

    msg->m_eMsgType = Put_Move;
    msg->m_iMsgLen = sizeof(MoveMsg);
    memcpy(msg->m_aMsgData, (void *)&moveMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendCopyMsg(CopyMsg copyMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(CopyMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(CopyMsg));

    msg->m_eMsgType = Put_Copy;
    msg->m_iMsgLen = sizeof(CopyMsg);
    memcpy(msg->m_aMsgData, (void *)&copyMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendNewFolderMsg(NewFolderMsg newFolderMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(NewFolderMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(NewFolderMsg));

    msg->m_eMsgType = Put_NewFolder;
    msg->m_iMsgLen = sizeof(NewFolderMsg);
    memcpy(msg->m_aMsgData, (void *)&newFolderMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

//重命名消息
int AbstractNetwork::sendRenameMsg(RenameMsg renameMsg)
{
    Msg *msg = (Msg*)new char[m_iMsgStructLen + sizeof(RenameMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(RenameMsg));

    msg->m_eMsgType = Put_Rename;
    msg->m_iMsgLen = sizeof(RenameMsg);
    memcpy(msg->m_aMsgData, (void*)&renameMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}


int AbstractNetwork::sendUploadMsg(UploadMsg uploadMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(UploadMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(UploadMsg));

    msg->m_eMsgType = Put_Upload;
    msg->m_iMsgLen = sizeof(UploadMsg);
    memcpy(msg->m_aMsgData, (void *)&uploadMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendDeleteMsg(DeleteMsg deleteMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(DeleteMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(DeleteMsg));

    msg->m_eMsgType = Put_Delete;
    msg->m_iMsgLen = sizeof(DeleteMsg);
    memcpy(msg->m_aMsgData, (void *)&deleteMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendShareMsg(ShareMsg shareMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(ShareMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(ShareMsg));

    msg->m_eMsgType = Put_Share;
    msg->m_iMsgLen = sizeof(ShareMsg);
    memcpy(msg->m_aMsgData, (void *)&shareMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendExitMsg(ExitMsg exitMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(ExitMsg) + 1];
    memset(msg, 0, m_iMsgStructLen + sizeof(ExitMsg));

    msg->m_eMsgType = Ack_Exit;
    msg->m_iMsgLen = sizeof(ExitMsg);
    memcpy(msg->m_aMsgData, (void *)&exitMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

//发送注册信息
int AbstractNetwork::sendRegisterMsg(RegisterMsg registerMsg)
{
    Msg *msg = (Msg *)new char[m_iMsgStructLen + sizeof(RegisterMsg) + 1];
    memset(msg, 0,  m_iMsgStructLen + sizeof(ExitMsg));

    msg->m_eMsgType = Put_Register;
    msg->m_iMsgLen = sizeof(RegisterMsg);
    memcpy(msg->m_aMsgData, (void*)&registerMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}


//收到的消息
void AbstractNetwork::recvAckOkMsg(Msg *msg)
{
    emit readyReadAckOKMsg();
}

void AbstractNetwork::recvAckErrorMsg(Msg *msg)
{
    ErrorMsg errorMsg;
    memcpy(&errorMsg, msg->m_aMsgData, msg->m_iMsgLen);
    //readyReadAckErrorMsg(errorMsg);
    emit readyReadAckErrorMsg(errorMsg);
}

void AbstractNetwork::recvReadyMsg(Msg *msg)
{
    ReadyMsg readyMsg;
    memcpy(&readyMsg, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadReadyMsg(readyMsg);
}

void AbstractNetwork::recvLoginMsg(Msg *msg)
{
    LoginMsg loginMsg;
    memcpy(&loginMsg, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadLoginMsg(loginMsg);
}

void AbstractNetwork::recvFileListMsg(Msg *msg)
{
    FileListsMsg fileListsMsg;
    memcpy(&fileListsMsg, msg->m_aMsgData, msg->m_iMsgLen);

    QByteArray byteArray(fileListsMsg.m_jsonFileList);
    emit readyReadFileListMsg(byteArray);
}

void AbstractNetwork::recvPreviewMsg(Msg *msg)
{
    PreviewArray previewArray;
    memcpy(&previewArray, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadPreviewMsg(previewArray);
}

void AbstractNetwork::recvDownloadMsg(Msg *msg)
{
    DownloadMsg downloadMsg;
    memcpy(&downloadMsg, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadDownloadMsg(downloadMsg);
}

void AbstractNetwork::recvMoveMsg(Msg *msg)
{
    MoveMsg moveMsg;
    memcpy(&moveMsg, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadMoveMsg(moveMsg);
}

void AbstractNetwork::recvNewFolderMsg(Msg *msg)
{
    NewFolderMsg newFolderMsg;
    memcpy(&newFolderMsg, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadNewFolderMsg(newFolderMsg);
}

void AbstractNetwork::recvRenameMsg(Msg *msg)
{
    RenameMsg renameMsg;
    memcpy(&renameMsg, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadRenameMsg(renameMsg);
}



void AbstractNetwork::recvUploadMsg(Msg *msg)
{
    UploadMsg uploadMsg;
    memcpy(&uploadMsg, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadUploadMsg(uploadMsg);
}

void AbstractNetwork::recvDeleteMsg(Msg *msg)
{
    DeleteMsg deleteMsg;
    memcpy(&deleteMsg, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadDeleteMsg(deleteMsg);
}

void AbstractNetwork::recvShareMsg(Msg *msg)
{
    ShareMsg shareMsg;
    memcpy(&shareMsg, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadShareMsg(shareMsg);
}

void AbstractNetwork::recvExitMsg(Msg *msg)
{
    ExitMsg exitMsg;
    memcpy(&exitMsg, msg->m_aMsgData, msg->m_iMsgLen);
    emit readyReadExitMsg(exitMsg);
}

int AbstractNetwork::sendMsg(Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    int ret = write((char *)msg, m_iMsgStructLen + msg->m_iMsgLen);
    flush();
    return ret;
}

void AbstractNetwork::recvMsg(Msg *msg)
{
    switch (msg->m_eMsgType){
    case Ack_OK:
        //确定成功
        recvAckOkMsg(msg);
        break;
    case Ack_Error:
        //确定错误
        recvAckErrorMsg(msg);
        break;
    case Ack_Ready:
        //准备就绪
        recvReadyMsg(msg);
        break;
    case Put_Login:
        //准备就绪
        recvLoginMsg(msg);
        break;
    case Get_FileLists:
        //准备就绪
        recvFileListMsg(msg);
        break;
    case Get_Preview:
        //准备就绪
        recvPreviewMsg(msg);
        break;
    case Get_Download:
        //准备就绪
        recvDownloadMsg(msg);
        break;
    case Put_Move:
        //准备就绪
        recvMoveMsg(msg);
        break;
    case Put_NewFolder:
        //准备就绪
        recvNewFolderMsg(msg);
        break;
    case Put_Upload:
        //准备就绪
        recvUploadMsg(msg);
        break;
    case Put_Delete:
        //准备就绪
        recvDeleteMsg(msg);
        break;
    case Put_Share:
        //准备就绪
        recvShareMsg(msg);
        break;
    case Ack_Exit:
        //准备就绪
        recvExitMsg(msg);
        break;
    }
}
