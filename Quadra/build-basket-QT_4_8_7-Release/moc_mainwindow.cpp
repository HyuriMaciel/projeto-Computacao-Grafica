/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../basket/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x08,
      51,   46,   11,   11, 0x08,
      81,   46,   11,   11, 0x08,
     111,   46,   11,   11, 0x08,
     141,   46,   11,   11, 0x08,
     171,   46,   11,   11, 0x08,
     201,   46,   11,   11, 0x08,
     231,   46,   11,   11, 0x08,
     261,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0checked\0on_checkBox_clicked(bool)\0"
    "arg1\0on_lineR_valueChanged(double)\0"
    "on_loneG_valueChanged(double)\0"
    "on_lineB_valueChanged(double)\0"
    "on_backR_valueChanged(double)\0"
    "on_backG_valueChanged(double)\0"
    "on_backB_valueChanged(double)\0"
    "on_lineS_valueChanged(double)\0"
    "on_pushButton_2_pressed()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_checkBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_lineR_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->on_loneG_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->on_lineB_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->on_backR_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->on_backG_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->on_backB_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->on_lineS_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_2_pressed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
