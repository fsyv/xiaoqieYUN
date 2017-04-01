#include "abstractnetwork.h"

#include "string.h"

AbstractNetwork::AbstractNetwork(QObject *parent):
    QObject(parent)
{

}

int AbstractNetwork::sendAckOkMsg()
{
    Msg msg;

    memset(&msg, 0, sizeof(Msg));

    msg.m_eMsgType = Ack_OK;
    msg.m_iMsgLen = 0;

    return sendMsg(&msg);
}

int AbstractNetwork::sendAckErrorMsg(ErrorMsg errorMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(ErrorMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(ErrorMsg));

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

    memset(&msg, 0, sizeof(Msg));

    msg.m_eMsgType = Ack_Ready;
    msg.m_iMsgLen = 0;

    return sendMsg(&msg);
}

int AbstractNetwork::sendLoginMsg(LoginMsg loginMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(LoginMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(LoginMsg));

    msg->m_eMsgType = Put_Login;
    msg->m_iMsgLen = sizeof(LoginMsg);
    memcpy(msg->m_aMsgData, (void *)&loginMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendFileListMsg(FileListsMsg fileListsMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(FileListsMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(FileListsMsg));

    msg->m_eMsgType = Get_FileLists;
    msg->m_iMsgLen = sizeof(FileListsMsg);
    memcpy(msg->m_aMsgData, (void *)&fileListsMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendPreviewMsg(PreviewMsg previewMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(PreviewMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(PreviewMsg));

    msg->m_eMsgType = Get_Preview;
    msg->m_iMsgLen = sizeof(PreviewMsg);
    memcpy(msg->m_aMsgData, (void *)&previewMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendDownloadMsg(DownloadMsg downloadMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(DownloadMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(DownloadMsg));

    msg->m_eMsgType = Get_Download;
    msg->m_iMsgLen = sizeof(DownloadMsg);
    memcpy(msg->m_aMsgData, (void *)&downloadMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendMoveMsg(MoveMsg moveMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(MoveMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(MoveMsg));

    msg->m_eMsgType = Put_Move;
    msg->m_iMsgLen = sizeof(MoveMsg);
    memcpy(msg->m_aMsgData, (void *)&moveMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendNewFolderMsg(NewFolderMsg newFolderMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(NewFolderMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(NewFolderMsg));

    msg->m_eMsgType = Put_NewFolder;
    msg->m_iMsgLen = sizeof(NewFolderMsg);
    memcpy(msg->m_aMsgData, (void *)&newFolderMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendUploadMsg(UploadMsg uploadMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(UploadMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(UploadMsg));

    msg->m_eMsgType = Put_Upload;
    msg->m_iMsgLen = sizeof(UploadMsg);
    memcpy(msg->m_aMsgData, (void *)&uploadMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendDeleteMsg(DeleteMsg deleteMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(DeleteMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(DeleteMsg));

    msg->m_eMsgType = Put_Delete;
    msg->m_iMsgLen = sizeof(DeleteMsg);
    memcpy(msg->m_aMsgData, (void *)&deleteMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendShareMsg(ShareMsg shareMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(ShareMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(ShareMsg));

    msg->m_eMsgType = Put_Share;
    msg->m_iMsgLen = sizeof(ShareMsg);
    memcpy(msg->m_aMsgData, (void *)&shareMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

int AbstractNetwork::sendExitMsg(ExitMsg exitMsg)
{
    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(ExitMsg)];
    memset(msg, 0, sizeof(Msg) + sizeof(ExitMsg));

    msg->m_eMsgType = Ack_Exit;
    msg->m_iMsgLen = sizeof(ExitMsg);
    memcpy(msg->m_aMsgData, (void *)&exitMsg, msg->m_iMsgLen);

    int ret = sendMsg(msg);

    delete msg;

    return ret;
}

void AbstractNetwork::recvAckOkMsg(Msg *msg)
{

}

void AbstractNetwork::recvAckErrorMsg(Msg *msg)
{
    ErrorMsg errorMsg;
    memcpy(&errorMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvReadyMsg(Msg *msg)
{
    ReadyMsg readyMsg;
    memcpy(&readyMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvLoginMsg(Msg *msg)
{
    LoginMsg loginMsg;
    memcpy(&loginMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvFileListMsg(Msg *msg)
{
    FileListsMsg fileListsMsg;
    memcpy(&fileListsMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvPreviewMsg(Msg *msg)
{
    PreviewMsg previewMsg;
    memcpy(&previewMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvDownloadMsg(Msg *msg)
{
    DownloadMsg downloadMsg;
    memcpy(&downloadMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvMoveMsg(Msg *msg)
{
    MoveMsg moveMsg;
    memcpy(&moveMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvNewFolderMsg(Msg *msg)
{
    NewFolderMsg newFolderMsg;
    memcpy(&newFolderMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvUploadMsg(Msg *msg)
{
    UploadMsg uploadMsg;
    memcpy(&uploadMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvDeleteMsg(Msg *msg)
{
    DeleteMsg deleteMsg;
    memcpy(&deleteMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvShareMsg(Msg *msg)
{
    ShareMsg shareMsg;
    memcpy(&shareMsg, msg->m_aMsgData, msg->m_iMsgLen);
}

void AbstractNetwork::recvExitMsg(Msg *msg)
{
    ExitMsg exitMsg;
    memcpy(&exitMsg, msg->m_aMsgData, msg->m_iMsgLen);
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
