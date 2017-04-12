#ifndef WIDGET_H
#define WIDGET_H
#include "basiccontrol/imagepreview.h"
#include <QtWidgets>
#include "poppler-qt5.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void openfile();

protected:
    void paintEvent(QPaintEvent *event);


public slots:
    void next_page();
    void before_page();
signals:
    void pixmap(const QPixmap &pix);
private:
    QPushButton *open;
    QString filename;
    QLabel *label;
    QImage image;
    Poppler::Document* document;
    int i = 0;

    ImagePreView *view;
};

#endif // WIDGET_H
