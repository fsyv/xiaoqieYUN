#include "basicwidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>
#include <QPushButton>
#include "basiccontrol/combobox.h"
#include "lineedit.h"
#include <QPixmap>
#include <QDebug>
BasicWidget::BasicWidget(QWidget *parent)
    : QWidget(parent)
{
   background_color = QColor(Qt::white); 
   setWindowFlags(Qt::FramelessWindowHint);
   close_buttonn = new QPushButton(this);
   QPixmap pix(":/resource/image/close.png");
   close_buttonn->setIcon(pix);
   close_buttonn->setFixedSize(pix.size());
   close_buttonn->setStyleSheet("border:none");
   drop = true;
   connect(close_buttonn, &QPushButton::clicked, this, [&](){this->close();});

}

BasicWidget::~BasicWidget()
{

}
void BasicWidget::hideCloseIcon()
{
    close_buttonn->hide();
}


void BasicWidget::setDroped(bool _drop)
{
    drop = _drop;
}

void BasicWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (pressed && drop) {
        QPoint p = e->globalPos();
        this->move(p.x() - point.x(), p.y() - point.y());
    }
}

void BasicWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
       pressed = true;
       point = e->pos();  // 按下左键时候的坐标。。
    }
}

void BasicWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
       pressed = false;
    }
}

void BasicWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(background_color));

    p.drawRect(0, 0, width(), height());
}

void BasicWidget::setBackgroundColor(const QColor &color)
{
    background_color = color;
    QPalette p = this->palette();
    p.setBrush(QPalette::Normal,QPalette::Background,QBrush(background_color));
    this->setPalette(p);
    this->update();
}

void BasicWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    close_buttonn->move(this->width()-close_buttonn->width(), 0);
    qDebug() << close_buttonn->width();
}
