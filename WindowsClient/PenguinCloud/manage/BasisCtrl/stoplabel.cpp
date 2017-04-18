#include "stoplabel.h"

StopLabel::StopLabel(QWidget *parent) :
    QLabel(parent),
    currentPictureIndex(0),
    m_bFlush(false)
{
    setPixmap(QPixmap("://Resource/stop_normal.png"));
    resize(16, 16);
    setScaledContents(true);
    //鼠标跟踪
    setMouseTracking(true);
}

StopLabel::~StopLabel()
{

}

void StopLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        setPixmap(QPixmap("://Resource/stop_press.png"));
    else
        event->ignore();

    m_bFlush = false;

    QLabel::mousePressEvent(event);
}

void StopLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setPixmap(QPixmap("://Resource/stop_normal.png"));
        emit stop();
    }
    else
        event->ignore();

    m_bFlush = true;

    QLabel::mousePressEvent(event);
}

void StopLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bFlush)
    {
        switch (currentPictureIndex++) {
        case 0:
            setPixmap(QPixmap("://Resource/stop_enter_1.png"));
            break;
        case 1:
            setPixmap(QPixmap("://Resource/stop_enter_2.png"));
            break;
        case 2:
            setPixmap(QPixmap("://Resource/stop_enter_3.png"));
            break;
        case 3:
            setPixmap(QPixmap("://Resource/stop_enter_4.png"));
            break;
        case 4:
            setPixmap(QPixmap("://Resource/stop_enter_5.png"));
            break;
        default:
            currentPictureIndex = 0;
            break;
        }
    }

    QLabel::mouseMoveEvent(event);
}

void StopLabel::enterEvent(QEvent *event)
{
    m_bFlush = true;
    QLabel::enterEvent(event);
}

void StopLabel::leaveEvent(QEvent *event)
{
    m_bFlush = true;
    setPixmap(QPixmap("://Resource/stop_normal.png"));
    QLabel::leaveEvent(event);
}
