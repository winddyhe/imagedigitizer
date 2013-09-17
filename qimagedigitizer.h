#ifndef QIMAGEDIGITIZER_H
#define QIMAGEDIGITIZER_H

#include <QtGui/QMainWindow>
#include <QMdiArea>
#include <QTreeView>
#include <QTextEdit>
#include <QSplitter>
#include <QMenu>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QKeySequence>
#include <QSignalMapper>
#include <QScrollBar>
#include <QStatusBar>
#include <QPoint>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QComboBox>

#include <QDebug>

#include "qpixmapwidget.h"
#include "QScrollPixmapWidget.h"

class QImageDigitizer : public QMainWindow
{
    Q_OBJECT

public:
    QImageDigitizer(QWidget *parent = 0);
    ~QImageDigitizer();

    void createWindowLayout();
    void createActions();
    void createMenus();
    void createToolBars();

protected:
    QScrollPixmapWidget* createMdiChild(QString pixPath);
    QMdiSubWindow* findMdiChild(const QString &fileName);
    QString getActiveChildFileName();

private slots:
    void openFile();
    void setMouseMode(int mode);
    void recordSelcetedPoint(QVector<QPoint> *posVec);
    void saveToFile();
    void activeWindow(QMdiSubWindow *window);
    void zoomIn();
    void zoomOut();
    void zoomValueChange(QString zoomValue);

signals:
    void mouseMode(EMouseMode mouseMode);
    void undoSignal();
    void zoomChanged(int zoom);

private:
    QMdiArea    *m_mdiArea;
    QTreeView   *m_treevImageList;
    QTextEdit   *m_textEdit;
    QSplitter   *m_mainSplitter;
    QSplitter   *m_rightSplitter;
    QComboBox   *m_comboxZoom;

    QMenu       *m_fileMenu;
    QMenu       *m_toolMenu;
    QToolBar    *m_fileToolBar;
    QToolBar    *m_toolToolBar;

    QAction     *m_openAct;
    QAction     *m_saveAct;
    QAction     *m_exitAct;
    QAction     *m_originModeAct;
    QAction     *m_generalModeAct;
    QAction     *m_pointModeAct;
    QAction     *m_undoAct;
    QAction     *m_zoomInAct;
    QAction     *m_zoomOutAct;

    QSignalMapper *m_modeSignalMapper;

    EMouseMode  m_curMouseMode;       //current mouse mode
    int         m_zoom;

    QString     m_activeWindowFileName;

    QVector<QPoint> *m_pointVec;
};

#endif // QIMAGEDIGITIZER_H
