#include "lineedit.h"
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
LineEdit::LineEdit(QWidget *parent ) : QLineEdit(parent)
{
    init();
    this->resize(200, 30);

    this->setStyleSheet("QLineEdit{background:#ffffff;color:gray;text-align:center;border-radius:15; font:15px}");
}
void LineEdit::init()
{
    // 初始配置
    this->setWindowFlags(Qt::FramelessWindowHint);

    //控件初始化
    h_layout = new QHBoxLayout;
    pix_label = new QLabel;
    pix_label->resize(this->size().height(), this->size().height());
    h_layout->addWidget(pix_label);
    h_layout->setContentsMargins(0,0,0,0);
    this->setLayout(h_layout);
}

void LineEdit::setLeftPixmap(const QString &filename)
{
    QPixmap pix(filename);
    pix_label->setPixmap(pix);
    int margin_width =(pix_label->size().width() - pix.size().width()) / 2 - 2;
    int margin_height = (pix_label->size().height() - pix.size().height()) / 2;
    pix_label->setContentsMargins(margin_width, margin_height, margin_width, margin_height);
    this->setTextMargins(pix.size().height() + 8,0,0,0);
    qDebug() << pix.size();
}

