/****************************************************************************
** Meta object code from reading C++ file 'qimagedigitizer.h'
**
** Created: Mon Oct 29 08:33:52 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qimagedigitizer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qimagedigitizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QImageDigitizer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   17,   16,   16, 0x05,
      49,   16,   16,   16, 0x05,
      67,   62,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   16,   16,   16, 0x08,
     100,   95,   16,   16, 0x08,
     125,  118,   16,   16, 0x08,
     163,   16,   16,   16, 0x08,
     183,  176,   16,   16, 0x08,
     212,   16,   16,   16, 0x08,
     221,   16,   16,   16, 0x08,
     241,  231,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QImageDigitizer[] = {
    "QImageDigitizer\0\0mouseMode\0"
    "mouseMode(EMouseMode)\0undoSignal()\0"
    "zoom\0zoomChanged(int)\0openFile()\0mode\0"
    "setMouseMode(int)\0posVec\0"
    "recordSelcetedPoint(QVector<QPoint>*)\0"
    "saveToFile()\0window\0activeWindow(QMdiSubWindow*)\0"
    "zoomIn()\0zoomOut()\0zoomValue\0"
    "zoomValueChange(QString)\0"
};

const QMetaObject QImageDigitizer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QImageDigitizer,
      qt_meta_data_QImageDigitizer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QImageDigitizer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QImageDigitizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QImageDigitizer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QImageDigitizer))
        return static_cast<void*>(const_cast< QImageDigitizer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QImageDigitizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mouseMode((*reinterpret_cast< EMouseMode(*)>(_a[1]))); break;
        case 1: undoSignal(); break;
        case 2: zoomChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: openFile(); break;
        case 4: setMouseMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: recordSelcetedPoint((*reinterpret_cast< QVector<QPoint>*(*)>(_a[1]))); break;
        case 6: saveToFile(); break;
        case 7: activeWindow((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        case 8: zoomIn(); break;
        case 9: zoomOut(); break;
        case 10: zoomValueChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QImageDigitizer::mouseMode(EMouseMode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QImageDigitizer::undoSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QImageDigitizer::zoomChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
