#ifndef FINISHEDWIDGET_H
#define FINISHEDWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QWidget;
class TopWidget;
class ManageListWidget;
class QVBoxLayout;
QT_END_NAMESPACE

class FinishedWidget : public QWidget
{
public:
    FinishedWidget(QWidget *parent = nullptr);
    ~FinishedWidget();

private:
    TopWidget *m_pTopWidget;
    ManageListWidget *m_pListWidget;
    QVBoxLayout *m_pVBosLayout;
};

#endif // FINISHEDWIDGET_H