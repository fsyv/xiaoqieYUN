﻿#include "connecttoserver.h"
#include <QDebug>

#include "tools/tools.h"

ConnectToServer* ConnectToServer::conn = nullptr;
QMutex ConnectToServer::mutex;

ConnectToServer::ConnectToServer(QObject *parent) :
    AbstractNetwork(parent),
    p_aRecvBuf(nullptr),
    p_cRearBuf(nullptr),
    p_cHeadBuf(nullptr)

{
    connect(this, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(displayState(QAbstractSocket::SocketState)));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connectToHost(SERVER_IP, SERVER_PORT);
    waitForConnected(1000);

    p_aRecvBuf = new char[2 * SEND_BUF_MAX_SIZE + 1];
    memset(p_aRecvBuf, 0, sizeof(char) * SEND_BUF_MAX_SIZE * 2);

    p_cRearBuf = p_aRecvBuf;
    p_cHeadBuf = p_aRecvBuf;

    m_iMsgLen = 0;
}

ConnectToServer::~ConnectToServer()
{
    if(p_aRecvBuf)
        delete p_aRecvBuf;
    p_aRecvBuf = nullptr;

    p_cRearBuf = p_aRecvBuf;
    p_cHeadBuf = p_aRecvBuf;
}

void ConnectToServer::readMessage()
{
    int recvRet = read(p_aRecvBuf, SEND_BUF_MAX_SIZE);

    //读数据错误
    if(recvRet < 0)
    {
        close();
        return;
    }

    m_iMsgLen += recvRet;

    if (m_iMsgLen > 2 * RECV_BUF_MAX_SIZE)
    {
        //消息长度大于缓存长度
        exit(-1);
    }

    //接收到总数据已经大于了RECV_BUF_MAX_SIZE
    //为了安全做一定处理
    if(m_iMsgLen > RECV_BUF_MAX_SIZE)
    {
        unsigned char crc[5];
        memset(crc, 0xAF, 4);
        //在收到得buf中查找0xAFAFAFAF标志位
        void *findMove = Tools::memstr(p_cHeadBuf, (memlen_t)m_iMsgLen, (void *)crc);

        if(findMove)
        {
            int move = (char *)findMove - p_aRecvBuf;
            m_iMsgLen -= move;
            memcpy(p_aRecvBuf, findMove, m_iMsgLen);
            p_cHeadBuf = p_aRecvBuf;
            p_cRearBuf += m_iMsgLen;
        }
        else
        {
            ErrorMsg errorMsg;
            errorMsg.m_eErrorType = DataPackError;
            sendAckErrorMsg(errorMsg);
            return;
        }


    }

    //如果收到包长度小于结构体长度，暂定为丢弃
    //实际可能会出现拆包情况，收到小于包长度得
    //数据包
    if(m_iMsgLen < m_iMsgStructLen)
    {
        //指正移到缓存后
        p_cRearBuf += m_iMsgLen;
        return;
    }

    p_aRecvBuf[m_iMsgLen] = '\0';

    //暂时没有想到好的解决方法
    //当且仅当发生TCP粘包时会执行这个loop
    //其它情况都无视这个loop
stickyPackageLoop:

    //翻译buf
    Msg *msg = (Msg *)p_cHeadBuf;

    //校验位是否正确，如果正确则执行下一步
    if(msg->m_uiCheckCrc != (unsigned int)0xAFAFAFAF)
    {
        //矫正
        //尽量校正，校正成功则继续
        //否则continue，直到这个数据包被放弃
        unsigned char crc[5];
        memset(crc, 0xAF, 4);
        //在收到得buf中查找0xAFAFAFAF标志位
        void *findMove = Tools::memstr(p_cHeadBuf, (memlen_t)m_iMsgLen, (void *)crc);

        if(findMove)
        {
            //找到标志位
            p_cHeadBuf = (char *)findMove;
            m_iMsgLen -= (p_cRearBuf - p_cHeadBuf);

            //重新翻译buf
            msg = (Msg *)p_cHeadBuf;
        }
        else
        {
            //没有找到标志位
            return;
        }

    }

    //一个错误得包
    if(msg->m_iMsgLen > RECV_BUF_MAX_SIZE - m_iMsgStructLen || msg->m_iMsgLen < 0)
    {
        ErrorMsg errorMsg;
        errorMsg.m_eErrorType = DataPackError;
        sendAckErrorMsg(errorMsg);
        return;
    }

    if(m_iMsgLen < m_iMsgStructLen + msg->m_iMsgLen)
    {
        //拆包
        p_cRearBuf += m_iMsgLen;
        return;
    }

    //投递数据包
    recvMsg(msg);
    m_iMsgLen -= m_iMsgStructLen + msg->m_iMsgLen;

    if(m_iMsgLen > 0)
    {
        //黏包
        p_cHeadBuf = p_cHeadBuf + m_iMsgStructLen + msg->m_iMsgLen;
        goto stickyPackageLoop;
    }

    //一轮结束pRearBuf和pHeadBuf指针重新指向recvBuf
    p_cRearBuf = p_aRecvBuf;
    p_cHeadBuf = p_aRecvBuf;

}

void ConnectToServer::displayState(QAbstractSocket::SocketState)
{

}

void ConnectToServer::displayError(QAbstractSocket::SocketError)
{
    qDebug()<< errorString();
}

ConnectToServer* ConnectToServer::getInstance()
{
    if(!conn)
    {
        mutex.lock();
        if(!conn)
        {
            conn = new ConnectToServer();
        }
        mutex.unlock();
    }

    //每次获取单实例时没网络不可达就会重新连接
    if(conn->state() == QAbstractSocket::UnconnectedState)
    {
        conn->connectToHost(SERVER_IP, SERVER_PORT);
        conn->waitForConnected(1000);
    }

    return conn;
}
