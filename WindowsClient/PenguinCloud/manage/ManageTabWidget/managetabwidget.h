#ifndef MANAGETABWIDGET_H
#define MANAGETABWIDGET_H

#include <QTabWidget>

#include <qDebug>

QT_BEGIN_HEADER
class QTabWidget;
QT_END_NAMESPACE

class ManageTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    ManageTabWidget(QWidget *parent = nullptr);
    ~ManageTabWidget();

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // MANAGETABWIDGET_H
