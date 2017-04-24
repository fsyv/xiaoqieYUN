#ifndef STOPLABEL_H
#define STOPLABEL_H

#include <QLabel>


class StopLabel : public QLabel
{
    Q_OBJECT
public:
    StopLabel(QWidget *parent = nullptr);
	~StopLabel();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    //搞着玩的
    int currentPictureIndex;
    bool m_bFlush;

signals:
    void stop();
};

#endif // STOPLABEL_H
