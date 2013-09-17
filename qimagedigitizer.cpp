#include "qimagedigitizer.h"

QImageDigitizer::QImageDigitizer(QWidget *parent)
    : QMainWindow(parent),
      m_curMouseMode(GENERALMODE),
      m_zoom(1),
      m_pointVec(NULL)
{
    createActions();
    createWindowLayout();
    createMenus();
    createToolBars();
}

QImageDigitizer::~QImageDigitizer()
{
}

void QImageDigitizer::createWindowLayout()
{
    m_textEdit = new QTextEdit();
    m_textEdit->setReadOnly(true);

    m_mdiArea  = new QMdiArea();
    m_mdiArea->setVerticalScrollBar(new QScrollBar(Qt::Vertical));
    m_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_mdiArea->setHorizontalScrollBar(new QScrollBar(Qt::Horizontal));
    m_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(activeWindow(QMdiSubWindow*)));

    m_comboxZoom = new QComboBox();
    QStringList zoomStr;
    zoomStr << "100%" << "200%" << "300%" << "400%" << "500%";
    m_comboxZoom->addItems(zoomStr);
    connect(m_comboxZoom, SIGNAL(currentIndexChanged(QString)), this, SLOT(zoomValueChange(QString)));

    m_mainSplitter = new QSplitter(Qt::Horizontal);
    m_mainSplitter->addWidget(m_mdiArea);
    m_mainSplitter->addWidget(m_textEdit);
    m_mainSplitter->setStretchFactor(0, 60);
    m_mainSplitter->setStretchFactor(1, 40);

    setCentralWidget(m_mainSplitter);

    setWindowTitle("Image Digitizer");
    setGeometry(100, 50, 900, 700);
}

void QImageDigitizer::createActions()
{
    m_openAct = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
    m_openAct->setShortcut(QKeySequence::New);
    m_openAct->setStatusTip(tr("Open a file"));
    connect(m_openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    m_saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    m_saveAct->setShortcut(QKeySequence::Save);
    m_saveAct->setStatusTip(tr("Save pos datas"));
    connect(m_saveAct, SIGNAL(triggered()), this, SLOT(saveToFile()));

    m_exitAct = new QAction(tr("E&xit"), this);
    m_exitAct->setShortcut(QKeySequence::Quit);
    m_exitAct->setStatusTip(tr("Exit the application"));
    connect(m_exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    m_modeSignalMapper = new QSignalMapper(this);

    m_generalModeAct = new QAction(QIcon(":/images/general.png"), tr("&General Mode"), this);
    //m_generalModeAct->setShortcut(tr("CTRL+KEY_G"));
    m_generalModeAct->setStatusTip(tr("Set mouse general mode"));
    connect(m_generalModeAct, SIGNAL(triggered()), m_modeSignalMapper, SLOT(map()));

    m_originModeAct = new QAction(QIcon(":/images/origin.png"),tr("O&rigin Mode"), this);
    //m_originModeAct->setShortcut(tr("CTRL+KEY_R"));
    m_originModeAct->setStatusTip(tr("Set mouse origin mode"));
    connect(m_originModeAct, SIGNAL(triggered()), m_modeSignalMapper, SLOT(map()));

    m_pointModeAct = new QAction(QIcon(":/images/point.png"), tr("&Point Mode"), this);
    //m_pointModeAct->setShortcut(tr("CTRL+KEY_P"));
    m_pointModeAct->setStatusTip(tr("Set mouse point mode"));
    connect(m_pointModeAct, SIGNAL(triggered()), m_modeSignalMapper, SLOT(map()));

    m_modeSignalMapper->setMapping(m_generalModeAct, (int)GENERALMODE);
    m_modeSignalMapper->setMapping(m_originModeAct, (int)ORIGINMODE);
    m_modeSignalMapper->setMapping(m_pointModeAct, (int)POINTMODE);
    connect(m_modeSignalMapper, SIGNAL(mapped(int)), this, SLOT(setMouseMode(int)));

    m_undoAct = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    m_undoAct->setShortcut(QKeySequence::Undo);
    m_undoAct->setStatusTip(tr("Undo"));
    connect(m_undoAct, SIGNAL(triggered()), this, SIGNAL(undoSignal()));

    m_zoomInAct = new QAction(QIcon(":/images/zoom_in.png"), tr("Zoom &in"), this);
    m_zoomInAct->setShortcut(QKeySequence::ZoomIn);
    m_zoomInAct->setStatusTip(tr("Zoom in"));
    connect(m_zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    m_zoomOutAct = new QAction(QIcon(":/images/zoom_out.png"), tr("Zoom O&ut"), this);
    m_zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    m_zoomOutAct->setStatusTip(tr("Zoom out"));
    connect(m_zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
}

void QImageDigitizer::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_openAct);
    m_fileMenu->addAction(m_saveAct);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAct);

    m_toolMenu = menuBar()->addMenu(tr("&Tool"));
    m_toolMenu->addAction(m_generalModeAct);
    m_toolMenu->addAction(m_originModeAct);
    m_toolMenu->addAction(m_pointModeAct);
    m_toolMenu->addSeparator();
    m_toolMenu->addAction(m_undoAct);
    m_toolMenu->addAction(m_zoomInAct);
    m_toolMenu->addAction(m_zoomOutAct);
}

void QImageDigitizer::createToolBars()
{
    m_fileToolBar = addToolBar(tr("File"));
    m_fileToolBar->addAction(m_openAct);
    m_fileToolBar->addAction(m_saveAct);

    m_toolToolBar = addToolBar(tr("Tool"));
    m_toolToolBar->addAction(m_generalModeAct);
    m_toolToolBar->addAction(m_originModeAct);
    m_toolToolBar->addAction(m_pointModeAct);
    m_toolToolBar->addAction(m_undoAct);
    m_toolToolBar->addSeparator();
    m_toolToolBar->addAction(m_zoomInAct);
    m_toolToolBar->addAction(m_zoomOutAct);
    m_toolToolBar->addWidget(m_comboxZoom);
    m_toolToolBar->addSeparator();
}

/*!
    slots
*/
void QImageDigitizer::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        QMdiSubWindow *existing = findMdiChild(fileName);
        if(existing)
        {
            m_mdiArea->setActiveSubWindow(existing);
        }
        /*set child widget size*/
        QScrollPixmapWidget *child = createMdiChild(fileName);
        child->show();
        m_mdiArea->activeSubWindow()->resize(child->getPixmapWidget()->getWidth()  + 50,
                                             child->getPixmapWidget()->getHeight() + 50 );
    }
}

void QImageDigitizer::setMouseMode(int mode)
{
    m_curMouseMode = (EMouseMode)mode;
    emit mouseMode(m_curMouseMode);
}

void QImageDigitizer::recordSelcetedPoint(QVector<QPoint> *posVec)
{
    m_pointVec = posVec;
    m_textEdit->clear();

    m_textEdit->setPlainText("Point Count: " + QString::number(m_pointVec->count()));
    foreach(QPoint point, *m_pointVec)
    {
        m_textEdit->setPlainText(m_textEdit->toPlainText() + tr("\n") + QString::number(point.x()) +
                                 tr("\t") + QString::number(point.y()));
    }
}

void QImageDigitizer::saveToFile()
{
    if(!m_pointVec)
        return;
    if(m_activeWindowFileName == "")
        return;
    QString dir = qApp->applicationDirPath();
    QFile file(dir + "\\data\\" + m_activeWindowFileName + tr(".txt"));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);

    foreach(QPoint pos, *m_pointVec)
    {
        out << pos.x() << "\t" << pos.y() << "\n";
    }
    file.close();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Tips");
    msgBox.setText("Data save success!");
    msgBox.exec();
}

void QImageDigitizer::activeWindow(QMdiSubWindow *window)
{
    if(!window)
        return;
    QScrollPixmapWidget *w = qobject_cast<QScrollPixmapWidget*>(window->widget());
    QFileInfo fi(w->getPixmapWidget()->getCurrentFile());
    if(fi.exists())
    {
        m_activeWindowFileName = fi.fileName();
    }
    m_pointVec = w->getPixmapWidget()->getPointVector();
    recordSelcetedPoint(m_pointVec);
}

void QImageDigitizer::zoomValueChange(QString zoomValue)
{
    m_zoom = (zoomValue.mid(0, zoomValue.length() - 1)).toInt() / 100;
    emit zoomChanged(m_zoom);
}

void QImageDigitizer::zoomIn()
{
    if(m_zoom < 5)
        m_zoom++;
    m_comboxZoom->setCurrentIndex(m_zoom - 1);
    emit zoomChanged(m_zoom);
}

void QImageDigitizer::zoomOut()
{
    if(m_zoom > 1)
        m_zoom--;
    m_comboxZoom->setCurrentIndex(m_zoom - 1);
    emit zoomChanged(m_zoom);
}

/*!
  aid function
*/
QScrollPixmapWidget* QImageDigitizer::createMdiChild(QString pixPath)
{
    //QPixmapWidget *child = new QPixmapWidget(pixPath);
    //child->setWindowTitle(pixPath);
    QScrollPixmapWidget *scrollChild = new QScrollPixmapWidget(pixPath);
    QPixmapWidget *child = scrollChild->getPixmapWidget();
    scrollChild->setWindowTitle(pixPath);
    QFileInfo fi(child->getCurrentFile());
    if(fi.exists())
    {
        m_activeWindowFileName = fi.fileName();
    }
    connect(this, SIGNAL(mouseMode(EMouseMode)), child, SLOT(onMouseMode(EMouseMode)));
    connect(child, SIGNAL(selectedPoint(QVector<QPoint>*)), this, SLOT(recordSelcetedPoint(QVector<QPoint>*)));
    connect(this, SIGNAL(undoSignal()), child, SLOT(onUndo()));
    connect(this, SIGNAL(zoomChanged(int)), child, SLOT(zoomChangedSlot(int)));
    m_mdiArea->addSubWindow(scrollChild);
    return scrollChild;
}

QMdiSubWindow* QImageDigitizer::findMdiChild(const QString &fileName)
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
    foreach(QMdiSubWindow *window, m_mdiArea->subWindowList())
    {
        QScrollPixmapWidget *mdiChild = qobject_cast<QScrollPixmapWidget*>(window->widget());
        if(mdiChild->getPixmapWidget()->getCurrentFile() == canonicalFilePath)
            return window;
    }
    return 0;
}
