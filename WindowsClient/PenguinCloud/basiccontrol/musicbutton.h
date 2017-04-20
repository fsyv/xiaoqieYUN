/**
  *继承QPushButton并且重写 四个事件。
  *实现鼠标形状的改变和 按钮图标的切换
  *
  */

#ifndef MUSICBUTTON_H
#define MUSICBUTTON_H

#include <QPushButton>
QT_BEGIN_NAMESPACE
class QEvent;
class QMouseEvent;
QT_END_NAMESPACE

class MusicButton : public QPushButton
{
public:
    /*
     *icons的顺序说明：  按照normal， normal_hover, pressed, pressed_hover的顺序传入
     */
    MusicButton(/*const QStringList &icons, int modalCount ,*/ QWidget* parent = Q_NULLPTR);
//    void setHoverIcon(const QString &);
//    void setIcons();
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
//    void mousePressEvent(QMouseEvent *);
//    void mousePressEvent(QMouseEvent *);

private:
//    bool isPressed;
//    bool isHovered;
    QString iconPath;
////  模态数量，包括hover和press但是要区分一种情况例如是播放按钮。第一次点击是播放，再点击就是暂停
////  如果 modalCount == 2，则是普通的按钮， 如果 == 4 则是 具有两种状态的按钮
//    int modalCount;
////  保存需要设置的Icon ， 如果modalCount = 2，icons.size() == 2; 否则  icon.size() == 4
//    QStringList icons;
};

#endif // MUSICBUTTON_H
