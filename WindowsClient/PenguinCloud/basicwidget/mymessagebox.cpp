#include "mymessagebox.h"

MyMessageBox::MyMessageBox(QWidget *parent) : BasicWidget(parent)
{
    resize(338, 163);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    setIcon(":/resource/image/linux.png");
    setTitle("提示");
    init();
}

void MyMessageBox::paintEvent(QPaintEvent *event)
{
    BasicWidget::paintEvent(event);

    QPainter p(this);
    p.save();
    p.setBrush(QBrush("#1296db"));
    p.setPen(Qt::NoPen);
    p.drawRect(0, 0, width(), 30);


    p.setBrush(QBrush(QColor::fromRgb(234, 238, 245)));
    p.drawRect(0, 128, width(), 35);

    p.restore();

}

void MyMessageBox::init()
{
    btn_1 = new QPushButton(this);
    btn_1->setFixedSize(72, 23);
    btn_1->move(170, 134);
    btn_1->setObjectName("btn_ok");

    btn_2 = new QPushButton(this);
    btn_2->setFixedSize(72, 23);
    btn_2->move(252, 134);
    btn_2->setObjectName("btn_ok");

    icon = new QLabel(this);
    icon->setFixedSize(48, 48);
    icon->move(30, 55);

    message = new QLabel(this);
    message->setFixedSize(200, 60);
    message->move(90, 48);
    message->setObjectName("message");

    connect(btn_1, &QPushButton::clicked, this, [this](){emit btn1();});
    connect(btn_2, &QPushButton::clicked, this, [this](){emit btn2();});

}
void MyMessageBox::setInfo(const QString &_message, const QString& btn1_text, const QString &btn2_text, IconType type)
{
    message->setText(_message);

    if(btn1_text.isEmpty())
    {
        btn_1->hide();
        btn_2->setText(btn2_text);
    }
    else
    {
        btn_1->setText(btn1_text);
        btn_2->setText(btn2_text);
    }

    switch(type)
    {
        case Warn: //警告
            icon->setPixmap(QPixmap(":/resource/image/hite.png"));
            break;
        default:
            break;
    }

}

MyMessageBox* MyMessageBox::showMessageBox(QWidget *parent, const QString &message,  const QString &btn1_text, const QString &btn2_text, IconType type)
{
    MyMessageBox *m = new MyMessageBox(parent);
    m->setInfo(message, btn1_text, btn2_text, type);
    m->show();

    return m;
}
