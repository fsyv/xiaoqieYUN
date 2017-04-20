//作为基础的窗口，重写了鼠标事件实现点击窗口任意位置拖拽
//一个接口用来设置窗口背景颜色  setBackgroundColor(const QColor &color);

#ifndef BasicWidget_H
#define BasicWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
class BasicWidget : public QWidget
{
    Q_OBJECT

public:
    BasicWidget(QWidget *parent = 0);
    virtual ~BasicWidget();

    //设置背景颜色
    void setBackgroundColor(const QColor &color);
    void setDroped(bool _drop);
    void hideCloseIcon();
    void setTitle(const QString &title);
    void setIcon(const QString &path);
    void setTranslucentBackground(bool);
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *event);
private:
    bool pressed = false;
    QPoint point;
    QColor background_color;
    QPushButton *close_buttonn;
    bool drop;
    QLabel *title;
    QLabel *icon;
};

#endif // BasicWidget_H
