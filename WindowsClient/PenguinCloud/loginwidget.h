#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include "basicwidget/basicwidget.h"
#include "basiccontrol/lineedit.h"
#include "network/msgtype.h"

//前置类声明

class QPushButton;
class QLineEdit;
class QComboBox;
class QLabel;
class QCheckBox;
class QTcpSocket;
class ConnectToServer;
class MainWidget;

class LoginWidget : public BasicWidget
{
    Q_OBJECT
public:
    LoginWidget(QWidget *parent = 0);
    ~LoginWidget();


public slots:
    void conn();
    void login_success(LoginMsg loginMsg);
private:
    void init(); // 设置窗口属性以及变量的初始化
    void setStyleSheetFromFile(const QString &filename);

    QPushButton *login_button; // 登陆按钮
    LineEdit *password_input; // 密码输入框
    LineEdit *username_input; // 用户账号输入框
    QLabel *label_title;
    QCheckBox *remember_password;
    QLabel *find_passord;
    ConnectToServer *m_pConnectToServer;
    MainWidget *m_pMainWidget;
};

#endif // LOGINWIDGET_H
