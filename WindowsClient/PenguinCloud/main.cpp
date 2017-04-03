#include <QApplication>
#include <QFile>
#include "loginwidget.h"
#include "mainwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/resource/qss/style.qss");
    if(file.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(file.readAll());
    }
    MainWidget w;
    w.show();

    return a.exec();
}
