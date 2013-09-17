#ifndef QSRCOLLPIXMAPWIDGET_H
#define QSRCOLLPIXMAPWIDGET_H

#include <QScrollArea>

#include "qpixmapwidget.h"

class QScrollPixmapWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit QScrollPixmapWidget(QString pixPath, QWidget *parent = 0);
    ~QScrollPixmapWidget();

    inline QPixmapWidget* getPixmapWidget() { return m_pixmapWidget; }

private:
    QPixmapWidget *m_pixmapWidget;
};

#endif // QSRCOLLPIXMAPWIDGET_H
