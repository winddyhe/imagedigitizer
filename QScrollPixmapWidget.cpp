#include "QScrollPixmapWidget.h"

QScrollPixmapWidget::QScrollPixmapWidget(QString pixPath, QWidget *parent) :
    QScrollArea(parent)
{
    m_pixmapWidget = new QPixmapWidget(pixPath);
    setWidget(m_pixmapWidget);
    viewport()->setBackgroundRole(QPalette::Dark);
    viewport()->setAutoFillBackground(true);
    setWindowTitle(m_pixmapWidget->getCurrentFile());
}

QScrollPixmapWidget::~QScrollPixmapWidget()
{
}
