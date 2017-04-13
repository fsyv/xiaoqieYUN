#ifndef CONNECTTOFILESERVER_H
#define CONNECTTOFILESERVER_H

#include <QUrl>
#include <qDebug>

#include "abstractnetwork.h"


class ConnectToFileServer : public AbstractNetwork
{
    Q_OBJECT
public:
    ConnectToFileServer(QUrl serverUrl,QObject *parent = nullptr);
    ~ConnectToFileServer();

    bool isConnected();

protected slots:
    void displayState(QAbstractSocket::SocketState);
    void displayError(QAbstractSocket::SocketError);
};

#endif // CONNECTTOFILESERVER_H
