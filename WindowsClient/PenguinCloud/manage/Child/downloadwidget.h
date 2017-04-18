#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QWidget;
class TopWidget;
class ManageListWidget;
class QVBoxLayout;
QT_END_NAMESPACE

class DownloadWidget : public QWidget
{
public:
    DownloadWidget(QWidget *parent = nullptr);
    ~DownloadWidget();

private:
    TopWidget *m_pTopWidget;
    ManageListWidget *m_pListWidget;
    QVBoxLayout *m_pVBosLayout;
};

#endif // DOWNLOADWIDGET_H
