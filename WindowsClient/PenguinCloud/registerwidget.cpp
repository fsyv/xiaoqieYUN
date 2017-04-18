#include "registerwidget.h"
#include <QCryptographicHash>
#include "basicwidget/mymessagebox.h"
RegisterWidget::RegisterWidget(QWidget *parent) : BasicWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    setBackgroundColor(QColor("#1296db"));
    resize(320, 380);
    init();
}

void RegisterWidget::init()
{

    //初始化对象
    title_content = new QLabel(this);

    btn_register = new QPushButton(tr("注册"), this);
    btn_cannel = new QPushButton(tr("取消"), this);
    btn_reset = new QPushButton(tr("重置"), this);

    le_username = new LineEdit(this);
    le_password = new LineEdit(this);

    //对象属性设置
    title_content->setPixmap(QPixmap(":/resource/image/register_bg.png"));

    le_username->setLeftPixmap(":/resource/image/username.png");
    le_password->setLeftPixmap(":/resource/image/password.png");

    le_username->setPlaceholderText("账号");
    le_password->setPlaceholderText("密码");
    le_password->setEchoMode(QLineEdit::Password);

    btn_register->setObjectName("button");
    btn_cannel->setObjectName("button");
    btn_reset->setObjectName("button");

    // 固定尺寸
    title_content->resize(200, 30);
    btn_register->setFixedSize(200, 30);
    btn_cannel->setFixedSize(80, 30);
    btn_reset->setFixedSize(80, 30);

    //绝对值定位
    title_content->move(55, 60);
    le_username->move(60, 120);
    le_password->move(60, 160);
    btn_register->move(60, 210);
    btn_reset->move(60, 250);
    btn_cannel->move(180, 250);

    //信号槽
    connect(btn_reset, &QPushButton::clicked, this, &RegisterWidget::reset);
    connect(btn_register, &QPushButton::clicked, this, &RegisterWidget::regis);
    connect(btn_cannel, &QPushButton::clicked, this, &RegisterWidget::canncel);
    m_pConnectToServer = ConnectToServer::getInstance();
    connect(m_pConnectToServer, &ConnectToServer::readyReadRegisterStatusMsg, this, RegisterWidget::showRegisterStatus);
}

void RegisterWidget::reset()
{
    le_username->clear();
    le_password->clear();
}

void RegisterWidget::regis()
{
    QString username = le_username->text();
    QString password = le_password->text();
//    if (m_pConnectToServer == NULL)
//    {
//        m_pConnectToServer = ConnectToServer::getInstance();
//        connect(m_pConnectToServer, &ConnectToServer::readyReadRegisterStatusMsg, this, RegisterWidget::showRegisterStatus);
//    }
    RegisterMsg registerMsg;
    memset(&registerMsg, 0, sizeof(RegisterMsg));

    memcpy(registerMsg.username, username.toUtf8().data(), username.length());
    memcpy(registerMsg.password, password.toUtf8().data(), password.length());

    m_pConnectToServer->sendRegisterMsg(registerMsg);

//    MyMessageBox *m = MyMessageBox::showMessageBox(this, "恭喜你，注册成功!", "", "确定", Warn);
//    connect(m, &MyMessageBox::btn2, this, [m, this](){m->close(); this->close();});

}

void RegisterWidget::canncel()
{
    this->close();
}

void RegisterWidget::showRegisterStatus(RegisterStatus rs)
{
    if (rs.status == 0)
    {
        MyMessageBox *m = MyMessageBox::showMessageBox(this, "恭喜你，注册成功!", "", "确定", Warn);
        connect(m, &MyMessageBox::btn2, this, [m, this](){m->close(); this->close();});
    }
    else if (rs.status == 1)
    {
        MyMessageBox *m = MyMessageBox::showMessageBox(this, "该用户已经被占用了!", "", "确定", Warn);
        connect(m, &MyMessageBox::btn2, this, [m, this](){m->close();});
    }

}


