#include "pdfwidget.h"
PdfWidget::PdfWidget(QWidget *parent)
    : QWidget(parent)
{
    view = new ImagePreView();
    view->show();
    connect(view, &ImagePreView::before, this, &PdfWidget::before_page);
    connect(view, &ImagePreView::next, this, &PdfWidget::next_page);
//    setPdfFile(" ");
}
PdfWidget::~PdfWidget()
{
    if(document)
        delete document;
    delete view;
}

void PdfWidget::setPdfFile(const QString &filename)
{
    if(filename.isEmpty())
        return;
    document = Poppler::Document::load(filename);
    if (!document || document->isLocked()) {
        delete document;
        return;
    }
    document->setRenderHint(Poppler::Document::TextAntialiasing);
    document->setRenderBackend(Poppler::Document::SplashBackend );

    setPage(0);
}

void PdfWidget::next_page()
{
    setPage(i++);
}

void PdfWidget::before_page()
{
   setPage(--i);
}

void PdfWidget::setPage(int i)
{
    if(i >=0 && i < document->numPages())
    {
        Poppler::Page* pdfPage = document->page(i);
        qDebug() << "PDF Size" << pdfPage->pageSize();
        image = pdfPage->renderToImage(72, 72, 0, 0, pdfPage->pageSize().width(), pdfPage->pageSize().height() );
        view->setPixmap(QPixmap::fromImage(image)/*.scaled(600, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)*/);
        if(image.isNull())
        {
            qDebug() << "error";
            return ;
        }
        update();
        delete pdfPage;
    }
}


