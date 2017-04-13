#ifndef CONNECTTOFILESERVER_H
#define CONNECTTOFILESERVER_H

#include <QUrl>

#include "abstractnetwork.h"


class ConnectToFileServer : public AbstractNetwork
{
    Q_OBJECT
public:
    ConnectToFileServer(QUrl serverUrl,QObject *parent = nullptr);

private:

};

#endif // CONNECTTOFILESERVER_H
