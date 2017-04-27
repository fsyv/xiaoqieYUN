#ifndef FINISHEDWIDGET_H
#define FINISHEDWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QWidget;
class TopWidget;
class ManageListWidget;
class QVBoxLayout;
class File;
class QListWidgetItem;
QT_END_NAMESPACE

class FinishedWidget : public QWidget
{
    Q_OBJECT
public:
    FinishedWidget(QWidget *parent = nullptr);
    ~FinishedWidget();

    void addTask(File *file);

private:
    TopWidget *m_pTopWidget;
    ManageListWidget *m_pListWidget;
    QVBoxLayout *m_pVBosLayout;

private slots:
    void cleanTask(QListWidgetItem *item);
};

#endif // FINISHEDWIDGET_H
