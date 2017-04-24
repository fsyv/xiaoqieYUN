#ifndef CLEANLABEL_H
#define CLEANLABEL_H

#include <QLabel>

class CleanLabel : public QLabel
{
    Q_OBJECT
public:
    CleanLabel(QWidget *parent = nullptr);
	~CleanLabel();
	
protected:
//    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void enterEvent(QEvent *event);
//    void leaveEvent(QEvent *event);
signals:
    void clean();
};

#endif // CLEANLABEL_H
