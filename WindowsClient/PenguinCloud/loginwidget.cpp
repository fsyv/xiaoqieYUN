#include "loginwidget.h"
#include <QComboBox>
#include <QLabel>
#include <QFile>
#include <QDebug>
#include <QCheckBox>
#include <QTcpSocket>
#include "mainwidget.h"
#include "logic/rwfile.h"
#include "registerwidget.h"
#include "network/connecttoserver.h"


LoginWidget::LoginWidget(QWidget *parent) :
    BasicWidget(parent),
    m_pConnectToServer(nullptr),
    m_pMainWidget(nullptr)
{

    this->setBackgroundColor("#1296db");
    resize(320,400);
    init();
    setStyleSheetFromFile(":/resource/qss/login.qss");

    RWFile rw(":/password.txt");
    QPair<QString, QString> info = rw.read();
    if(!info.first.isEmpty())
        username_input->setText(info.first);
    if(!info.second.isEmpty())
        password_input->setText(info.second);

    m_pConnectToServer = ConnectToServer::getInstance();

    connect(m_pConnectToServer, SIGNAL(readyReadLoginMsg(LoginMsg)), this, SLOT(login_success(LoginMsg)));
}

LoginWidget::~LoginWidget()
{
//    m_pConnectToServer = nullptr;

//    if(m_pMainWidget)
//       delete m_pMainWidget;
//    m_pMainWidget = nullptr;
}

void LoginWidget::init()
{

    label_title = new QLabel(this);
    QPixmap pix(":/resource/image/title.png");
    label_title->setPixmap(pix);
    label_title->move((this->width() - pix.width()) /2, 60);
    username_input = new LineEdit(this);
    username_input->setLeftPixmap(":/resource/image/username.png");
    password_input = new LineEdit(this);
    password_input->setLeftPixmap(":/resource/image/password.png");
    login_button = new QPushButton("登录",this);
    login_button->resize(115,30);
    regist_button = new QPushButton(tr("注册"), this);
    regist_button->resize(65, 30);
//    remember_password = new QCheckBox("记住密码", this);
//    find_passord = new QLabel("找回密码", this);

    //绝对定位
    username_input->move((this->width() - username_input->width()) /2, 150);
    password_input->move((this->width() - password_input->width()) /2 ,190);
    login_button->move(60, 250);
    regist_button->move(195 ,250);
//    remember_password->move(75, 225);
//    find_passord->move(180, 225);
//    find_passord->setObjectName("find_passord");
    //默认配置
    username_input->setPlaceholderText("账号");
    password_input->setPlaceholderText("密码");
    password_input->setEchoMode(QLineEdit::Password);
    login_button->setObjectName("button");
    regist_button->setObjectName("button");

    connect(login_button, &QPushButton::clicked, this, &LoginWidget::conn);
    connect(regist_button, &QPushButton::clicked, this, &LoginWidget::registerwidget);

}
void LoginWidget::setStyleSheetFromFile(const QString &filename)
{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(file.readAll());
        qDebug() << this->styleSheet();
    }
}
void LoginWidget::conn()
{
    login_button->setText(tr("login..."));
    LoginMsg loginMsg;
    memset(&loginMsg, 0, sizeof(LoginMsg));

    loginMsg.m_iLoginStatus = PUT_LOGIN;
    memcpy(loginMsg.m_aUserName, username_input->text().toUtf8().data(), username_input->text().length());
    memcpy(loginMsg.m_aUserPass, password_input->text().toUtf8().data(), password_input->text().length());
    ConnectToServer::getInstance()->sendLoginMsg(loginMsg);
}

void LoginWidget::registerwidget()
{
    RegisterWidget *w = new RegisterWidget(this);
    w->show();
}

void LoginWidget::login_success(LoginMsg loginMsg)
{
    qDebug() << "login_success";

    if(loginMsg.m_iLoginStatus == LOGIN_SUCCESS)
    {
        hide();

        if(m_pMainWidget)
            delete m_pMainWidget;

        m_pMainWidget = new MainWidget;
        m_pMainWidget->setUserName(QString(loginMsg.m_aUserName));

        m_pMainWidget->show();
    }
    else if(loginMsg.m_iLoginStatus == LOGIN_FAILED_PASSWD)
    {

    }
    else if(loginMsg.m_iLoginStatus == LOGIN_FAILED_USERNAME)
    {

    }

}
