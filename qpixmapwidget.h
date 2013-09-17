#ifndef QPIXMAPWIDGET_H
#define QPIXMAPWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QVector>
#include <QPainter>
#include <QMouseEvent>
#include <QFileInfo>
#include <QPalette>
#include <QCursor>
#include <QPoint>
#include <QScrollArea>
#include <QLabel>
#include <QHBoxLayout>
#include <QSize>

enum EMouseMode {
    GENERALMODE,
    ORIGINMODE,
    POINTMODE
};

class QPixmapWidget : public QWidget
{
    Q_OBJECT
public:
    QPixmapWidget(QString pixPath = "", QWidget *parent = 0);

    ~QPixmapWidget();

    void setPixmap(QString pixPath);

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);

    inline QString getCurrentFile() { return m_curFile; }
    inline void setCurrentFile(const QString &fileName)
    {
        m_curFile = QFileInfo(fileName).canonicalFilePath();
    }

    inline int getWidth()  { return m_width; }
    inline int getHeight() { return m_height;}
    inline QVector<QPoint>* getPointVector() { return m_pointVec; }

public slots:
    void onMouseMode(EMouseMode mouseMode);
    void onUndo();
    void zoomChangedSlot(int zoom);

protected:
    QPoint coordTranslate(QPoint pos);

signals:
    void selectedPoint(QVector<QPoint> *posVec);

private:
    QString m_curFile;

    QPixmap m_pixmap;
    int     m_width;
    int     m_height;
    int     m_zoom;     //Ëõ·ÅÒò×Ó

    int     m_xLine;
    int     m_yLine;

    QPoint  m_origin;
    QPoint  m_curSelectedPoint;
    QVector<QPoint> *m_pointVec;
    QVector<QPoint> *m_pointVecForDraw;

    EMouseMode m_curMouseMode;
};

#endif // QPIXMAPWIDGET_H
