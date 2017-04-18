#ifndef DOWNLOADTOPWIDGET_H
#define DOWNLOADTOPWIDGET_H

#include "topwidget.h"

QT_BEGIN_NAMESPACE
class TopWidget;
QT_END_NAMESPACE


class DownloadTopWidget : public TopWidget
{
    Q_OBJECT
public:
    DownloadTopWidget(QWidget *parent = nullptr);
    ~DownloadTopWidget();

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // DOWNLOADTOPWIDGET_H
