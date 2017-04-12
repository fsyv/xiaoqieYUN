#include <QApplication>
#include <QFile>
#include "loginwidget.h"
#include "mainwidget.h"
#include "basiccontrol/imagepreview.h"
#include "widget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/resource/qss/style.qss");
    if(file.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(file.readAll());
    }

//    ImagePreView w;
    LoginWidget w;
//    Widget w;
    w.show();
//    MainWidget w;s
//    w.show();

    return a.exec();
}
