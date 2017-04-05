#ifndef UPLOADFILETOSERVER_H
#define UPLOADFILETOSERVER_H

#include "abstractnetwork.h"

#include <QFileInfo>
#include <QTcpSocket>
#include <qDebug>

class UploadFileToServer : public AbstractNetwork
{
    Q_OBJECT
public:
    UploadFileToServer(const QFileInfo &info, UploadMsg uploadMsg, QObject *parent = nullptr);

private:
    QTcpSocket *m_pTcpSocket;
    QFileInfo m_fileinfo;

    //实现父类sendMsg方法
    int sendMsg(Msg *msg);
    void updateFile();

protected slots:
    void readMessage();
    void displayError(QAbstractSocket::SocketError);
};

#endif // UPLOADFILETOSERVER_H
