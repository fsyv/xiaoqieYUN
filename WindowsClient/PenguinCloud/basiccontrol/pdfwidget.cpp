#include "pdfwidget.h"
PdfWidget::PdfWidget(QWidget *parent)
    : QWidget(parent)
{
    view = new ImagePreView();
    view->show();
    connect(view, &ImagePreView::before, this, &PdfWidget::before_page);
    connect(view, &ImagePreView::next, this, &PdfWidget::next_page);
}
PdfWidget::~PdfWidget()
{
    if(document)
        delete document;
    delete view;
}

void PdfWidget::setPdfFile(const QString &filename)
{

    document = Poppler::Document::load(filename);
    if (!document || document->isLocked()) {
        delete document;
        return;
    }
    document->setRenderHint(Poppler::Document::TextAntialiasing);
    document->setRenderBackend(Poppler::Document::SplashBackend );
}

void PdfWidget::next_page()
{
    Poppler::Page* pdfPage = document->page(++i);
    image = pdfPage->renderToImage(92.56, 92.56, 0, 0, 600,800 );
    view->setPixmap(QPixmap::fromImage(image).scaled(600, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    if(image.isNull())
    {
        qDebug() << "error";
        return ;
    }
    update();
    delete pdfPage;
}

void PdfWidget::before_page()
{
    if(i <= 0)
        return;
    Poppler::Page* pdfPage = document->page(--i);
    image = pdfPage->renderToImage(92.56, 92.56, 0, 0, 600,800 );
    view->setPixmap(QPixmap::fromImage(image).scaled(600, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    if(image.isNull())
    {
        qDebug() << "error";
        return ;
    }
    update();
    delete pdfPage;
}
