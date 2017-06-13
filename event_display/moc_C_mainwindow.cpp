/****************************************************************************
** Meta object code from reading C++ file 'C_mainwindow.h'
**
** Created: Wed Dec 7 17:16:46 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "C_mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_C_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      23,   13,   13,   13, 0x08,
      32,   13,   13,   13, 0x08,
      41,   13,   13,   13, 0x08,
      48,   13,   13,   13, 0x08,
      60,   13,   13,   13, 0x08,
      67,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_C_MainWindow[] = {
    "C_MainWindow\0\0OpenXZ()\0OpenYZ()\0"
    "Open3D()\0Open()\0OpenEvent()\0next()\0"
    "last()\0"
};

const QMetaObject C_MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_C_MainWindow,
      qt_meta_data_C_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &C_MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *C_MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *C_MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_C_MainWindow))
        return static_cast<void*>(const_cast< C_MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int C_MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OpenXZ(); break;
        case 1: OpenYZ(); break;
        case 2: Open3D(); break;
        case 3: Open(); break;
        case 4: OpenEvent(); break;
        case 5: next(); break;
        case 6: last(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
