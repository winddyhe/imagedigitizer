#include <QtGui/QApplication>
#include "qimagedigitizer.h"
#include "QScrollPixmapWidget.h"

#include <QScrollArea>
#include <QPalette>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QImageDigitizer w;
    w.show();

//    QScrollPixmapWidget w("F:/Nokia/project/hh/imagedigitizer-build-desktop"
//                          "-Qt_4_7_4_for_Desktop_-_MinGW_4_4__Qt_SDK__Debug/srceenshot/Screenshot_5.jpg");

//    QPixmapWidget *w = new QPixmapWidget("F:/Nokia/project/hh/imagedigitizer/images/open.png");
//    QScrollArea scrollArea;
//    scrollArea.setWidget(w);
//    scrollArea.viewport()->setBackgroundRole(QPalette::Dark);
//    scrollArea.viewport()->setAutoFillBackground(true);
//    scrollArea.show();
    return a.exec();
}
