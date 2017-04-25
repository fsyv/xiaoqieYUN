#pragma once
#pragma execution_character_set("utf-8")


#include <QWidget>

QT_BEGIN_NAMESPACE
class PictureLabel;
class QLabel;
class CleanLabel;
class QListWidgetItem;
class QListWidget;
class File;
QT_END_NAMESPACE

class FinishedList : public QWidget
{
    Q_OBJECT
public:
    explicit FinishedList(QListWidget *listWidget, QWidget *parent = 0);
    ~FinishedList();

    void setFile(File *file);
    File *getFile() const;
    QListWidgetItem *getListWidgetItem() const;
private:
    void initWidget();
    void setWidgetLayout();
    void destroyWidget();

    void setIco();
    void setName(QString name);
    void setSize(qint64 totalSize);

    File *m_pFile;

    PictureLabel *m_pFileIco;
    QLabel *m_pFileName;
    QLabel *m_pFileSize;
    QLabel *m_pFinishedTime;
    CleanLabel *m_pCleanButton;
    QListWidgetItem *m_pListWidgetItem;
protected:
    void resizeEvent(QResizeEvent *e);
signals:
    void clean(QListWidgetItem *);
public slots:
    void clean_cleanButton();
};
