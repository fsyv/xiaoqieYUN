#include "loginwidget.h"
#include <QComboBox>
#include <QLabel>
#include <QFile>
#include <QDebug>
#include <QCheckBox>
#include <QTcpSocket>
#include "logic/rwfile.h"
#include "logic/login.h"

LoginWidget::LoginWidget(QWidget *parent) : BasicWidget(parent)
{

    this->setBackgroundColor("#0698f5");
    resize(320,400);
    init();
    setStyleSheetFromFile(":/resource/qss/login.qss");

    RWFile rw(":/password.txt");
    QPair<QString, QString> info = rw.read();
    if(!info.first.isEmpty())
        username_input->setText(info.first);
    if(!info.second.isEmpty())
        password_input->setText(info.second);

}

LoginWidget::~LoginWidget()
{

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
    login_button->resize(200,30);
    remember_password = new QCheckBox("记住密码", this);
    find_passord = new QLabel("找回密码", this);

    //绝对定位
    username_input->move((this->width() - username_input->width()) /2, 150);
    password_input->move((this->width() - password_input->width()) /2 ,183);
    login_button->move((this->width() - login_button->width()) /2 ,250);
    remember_password->move(75, 225);
    find_passord->move(180, 225);
    find_passord->setObjectName("find_passord");
    //默认配置
    username_input->setPlaceholderText("账号");
    password_input->setPlaceholderText("密码");
    password_input->setEchoMode(QLineEdit::Password);
    login_button->setObjectName("login_button");


    connect(login_button, &QPushButton::clicked, this, &LoginWidget::conn);

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
   // sock = ConnectToServer::getInstance();
    login_button->setText(tr("login..."));
   // connect(sock, &ConnectToServer::readyRead, this, &LoginWidget::login_success);
   // if(sock->state() != QAbstractSocket::UnconnectedState)
    //{
        QString data = username_input->text() + "@" + password_input->text();
        Login *login = new Login();
        login->sendUserInfo(data);

  //  }else
    //{
       // login_button->setText("Check NetWork");
      //  return;
   // }
   // connect(sock, &ConnectToServer::readyRead, this, &LoginWidget::login_success);
}

void LoginWidget::login_success()
{
    QString str = sock->readAll();
    if(str != "")
    {
        login_button->setText(tr("login success"));
        sock->close();
    }

    disconnect(sock, &ConnectToServer::readyRead, this, &LoginWidget::login_success);
}
