#ifndef UPLOADWIDGET_H
#define UPLOADWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QWidget;
class TopWidget;
class ManageListWidget;
class QVBoxLayout;
QT_END_NAMESPACE

class UploadWidget : public QWidget
{
public:
    UploadWidget(QWidget *parent = nullptr);
	~UploadWidget();

private:
    TopWidget *m_pTopWidget;
    ManageListWidget *m_pListWidget;
    QVBoxLayout *m_pVBosLayout;
};

#endif // UPLOADWIDGET_H