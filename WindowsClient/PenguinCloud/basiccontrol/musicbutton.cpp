#include "musicbutton.h"

#include<QEvent>
#include <QDebug>
#include <QMouseEvent>
MusicButton::MusicButton(/*const QStringList &_icons, int _modalCount, */QWidget *parent)
    : QPushButton(parent)
//    , icons(_icons)
//    , modalCount(_modalCount)
{
//    isPressed = false;
//    isHovered = false;
    setStyleSheet("border:none;");
}

void MusicButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::PointingHandCursor);
//    isHovered = true;
//    setIcons();
}

void MusicButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
//    isHovered = false;
//    setIcons();
}

//void MusicButton::mousePressEvent(QMouseEvent *event)
//{
//    isPressed = true;
//    setIcons();
//}

//void MusicButton::mousePressEvent(QMouseEvent *event)
//{
//    isPressed = false;
//    setIcons();
//}

//void MusicButton::setIcons()
//{
//    if(modalCount == 2)     //这个按钮只有一种状态
//    {
//        if(isHovered)
//            setIcon(QIcon(icons[1]));
//        else
//            setIcon(QIcon(icons[0]));

//    }
//    else                    // modalCount == 4
//    {
//        if(isPressed)       //点击次数为奇数时的状态。
//        {
//            if(isHovered)
//                setIcon(QIcon(icons[3]));
//            else
//                setIcon(QIcon(icons[2]));
//        }
//        else               //点击次数为偶数时的状态。
//        {
//            if(isHovered)
//                setIcon(QIcon(icons[1]));
//            else
//                setIcon(QIcon(icons[0]));
//        }
//    }

//}
