#ifndef FILETABLEWIDGET_H
#define FILETABLEWIDGET_H

#include <QTableWidget>

class FileTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    FileTableWidget(QWidget *parent = nullptr);
    void setTableRow(QVector<QStringList> &_vec);
public slots:

private:
    void init();

    QVector<QStringList> files;

};

#endif // FILETABLEWIDGET_H
