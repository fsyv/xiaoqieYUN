#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QWidget>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

class TopWidget : public QWidget
{
    Q_OBJECT
public:
    TopWidget(QWidget *parent = nullptr);
    ~TopWidget();
};

#endif // TOPWIDGET_H
