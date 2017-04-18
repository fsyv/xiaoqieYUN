#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QtWidgets>
#include "basiccontrol/lineedit.h"
#include "basicwidget/basicwidget.h"
#include "network/connecttoserver.h"

class RegisterWidget : public BasicWidget
{
    Q_OBJECT
public:
    RegisterWidget(QWidget *parent = 0);

public slots:
    void reset();
    void regis();
    void canncel();
    void showRegisterStatus(RegisterStatus);

private:
    void init();

    QLabel *title_content;

    LineEdit *le_username;
    LineEdit *le_password;

    QPushButton *btn_register;
    QPushButton *btn_cannel;
    QPushButton *btn_reset;

    ConnectToServer *m_pConnectToServer;
};

#endif // REGISTERWIDGET_H
