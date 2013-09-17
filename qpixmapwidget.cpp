#include "qpixmapwidget.h"

#include <QDebug>


QPixmapWidget::QPixmapWidget(QString pixPath, QWidget *parent) :
    QWidget(parent),
    m_zoom(1),
    m_xLine(0),
    m_yLine(0),
    m_origin(0, 0),
    m_curMouseMode(GENERALMODE)
{
    m_pointVec = new QVector<QPoint>();
    m_pointVecForDraw = new QVector<QPoint>();
    setMouseTracking(true);
    setPixmap(pixPath);
    setWindowFlags(Qt::SubWindow);
    setAutoFillBackground(true);
    //setMaximumSize(m_width, m_height);
}

QPixmapWidget::~QPixmapWidget()
{
}

void QPixmapWidget::setPixmap(QString pixPath)
{
    m_curFile = pixPath;
    m_pixmap.load(pixPath);
    m_width = m_pixmap.width();
    m_height = m_pixmap.height();
    resize(m_width, m_height);
    qDebug() << m_curFile;
    qDebug()<< "Width:" << m_width << ", Height:" << m_height;
}

void QPixmapWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    QPen pen;
    pen.setWidth(m_zoom);
    painter.drawImage(0, 0, m_pixmap.toImage().scaled(QSize(m_width, m_height)));
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawLine(0, m_origin.y() * m_zoom, width(), m_origin.y() * m_zoom);
    painter.drawLine(m_origin.x() * m_zoom, 0, m_origin.x() * m_zoom, height());
    painter.drawLine(width(), m_origin.y() * m_zoom, width() - 8, (m_origin.y() + 3) * m_zoom);
    painter.drawLine(width(), m_origin.y() * m_zoom, width() - 8, (m_origin.y() - 3) * m_zoom);
    painter.drawLine(m_origin.x() * m_zoom, 0, (m_origin.x() + 3) * m_zoom, 8);
    painter.drawLine(m_origin.x() * m_zoom, 0, (m_origin.x() - 3) * m_zoom, 8);
    painter.drawText(5, 20, "X:" + QString::number(m_curSelectedPoint.x())+
                     ", Y:" + QString::number(m_curSelectedPoint.y()));
    pen.setColor(Qt::red);
    painter.setPen(pen);
    foreach(QPoint point, *m_pointVecForDraw)
    {
        painter.drawLine((point.x() - 3) * m_zoom, (point.y() - 3) * m_zoom,
                         (point.x() + 3) * m_zoom, (point.y() + 3) * m_zoom);
        painter.drawLine((point.x() + 3) * m_zoom, (point.y() - 3) * m_zoom,
                         (point.x() - 3) * m_zoom, (point.y() + 3) * m_zoom);
    }

    if(m_curMouseMode == GENERALMODE)
    {
        setCursor(QCursor(Qt::ArrowCursor));
        pen.setColor(Qt::red);
        painter.setPen(pen);
    }
    else if(m_curMouseMode == ORIGINMODE)
    {
        setCursor(QCursor(Qt::CrossCursor));
        pen.setColor(Qt::yellow);
        pen.setStyle(Qt::DashLine);
        painter.setPen(pen);
        painter.drawLine(0, m_yLine, width(), m_yLine);
        painter.drawLine(m_xLine, 0, m_xLine, height());
    }
    else if(m_curMouseMode == POINTMODE)
    {
        setCursor(QCursor(Qt::PointingHandCursor));

        pen.setColor(Qt::red);
        painter.setPen(pen);
        painter.drawLine(0, m_yLine, width(), m_yLine);
        painter.drawLine(m_xLine, 0, m_xLine, height());
    }
}

void QPixmapWidget::mousePressEvent(QMouseEvent *e)
{
    if(m_curMouseMode == ORIGINMODE)
    {
        m_origin = e->pos() / m_zoom;
        update();
    }
}

void QPixmapWidget::mouseMoveEvent(QMouseEvent *e)
{
    m_xLine = e->pos().x();
    m_yLine = e->pos().y();
    m_curSelectedPoint = coordTranslate(e->pos());
    update();
}

void QPixmapWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_curMouseMode == POINTMODE)
    {
        m_curSelectedPoint = coordTranslate(e->pos());
        m_pointVec->push_back(m_curSelectedPoint);
        m_pointVecForDraw->push_back(e->pos() / m_zoom);
        emit selectedPoint(m_pointVec);
    }
}

/*!
  draw image into widget background, reduce number of drawing
*/
void QPixmapWidget::resizeEvent(QResizeEvent *e)
{
      QWidget::resizeEvent(e);
}

void QPixmapWidget::onMouseMode(EMouseMode mouseMode)
{
    m_curMouseMode = mouseMode;
    qDebug() << "Mouse Mode:" << m_curMouseMode;
    update();
}

void QPixmapWidget::onUndo()
{
    if(m_pointVec->count())
    {
        m_pointVec->pop_back();
        m_pointVecForDraw->pop_back();
        emit selectedPoint(m_pointVec);
        update();
    }
}

void QPixmapWidget::zoomChangedSlot(int zoom)
{
    if(m_zoom != zoom)
    {
        m_zoom = zoom;
        m_width = m_pixmap.width() * m_zoom;
        m_height = m_pixmap.height() * m_zoom;
        resize(m_width, m_height);
        qDebug() << "Width:" << m_width << ", Height:" << m_height;
        update();
    }
}

QPoint QPixmapWidget::coordTranslate(QPoint pos)
{
    QPoint newPos;
    newPos.setX(pos.x() - m_origin.x() * m_zoom);
    newPos.setY(m_origin.y() * m_zoom - pos.y());
    newPos = newPos / m_zoom;
    return newPos;
}

