#ifndef CONNECTTOSERVER_H
#define CONNECTTOSERVER_H

#include <QObject>
#include <QTcpSocket>
class ConnectToServer : public QTcpSocket
{
    Q_OBJECT
public:
    static ConnectToServer* getInstance();
private:
    ConnectToServer(QObject *parent = nullptr);
    static ConnectToServer* conn;
};

#endif // CONNECTTOSERVER_H
