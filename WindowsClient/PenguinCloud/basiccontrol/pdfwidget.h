#ifndef WIDGET_H
#define WIDGET_H
#include "basiccontrol/imagepreview.h"
#include <QtWidgets>
#include "poppler-qt5.h"
class PdfWidget : public QWidget
{
    Q_OBJECT

public:
    PdfWidget(QWidget *parent = 0);
    ~PdfWidget();
    void setPdfFile(const QString &filename);
    void setPage(int i);
public slots:
    void next_page();
    void before_page();
signals:
    void pixmap(const QPixmap &pix);
private:
    QImage image;
    Poppler::Document* document;
    int i = 0;

    ImagePreView *view;
};

#endif // WIDGET_H
