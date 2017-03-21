#include <QApplication>
#include "network/tcpnetwork.h"
#include "loginwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TCPNetwork *tcpNetwork = TCPNetwork::getTCPNetworkInstance();
    tcpNetwork->connectServer();

    LoginWidget w;
    w.show();

    return a.exec();
}
