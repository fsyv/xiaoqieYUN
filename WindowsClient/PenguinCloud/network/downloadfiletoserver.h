#ifndef DOWNLOADFILETOSERVER_H
#define DOWNLOADFILETOSERVER_H

#include "abstractnetwork.h"

#include <fstream>

using namespace std;

#include <QFileInfo>
#include <QTcpSocket>
#include <QDebug>
class DownloadFileToServer : public AbstractNetwork
{
    Q_OBJECT
public:
    DownloadFileToServer(DownloadMsg downloadMsg, QObject *parent = nullptr);
private:
    QTcpSocket *m_pTcpSocket;
    QFileInfo m_fileinfo;

    ofstream fout;

    //实现父类sendMsg方法
    int sendMsg(Msg *msg);

protected slots:
    void readMessage();
    void displayError(QAbstractSocket::SocketError);
};

#endif // DOWNLOADFILETOSERVER_H
