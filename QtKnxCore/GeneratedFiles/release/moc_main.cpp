/****************************************************************************
** Meta object code from reading C++ file 'main.h'
**
** Created: Fri 9. Mar 20:28:41 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../main.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainSignalHandler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      29,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   40,   18,   18, 0x0a,
      64,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainSignalHandler[] = {
    "MainSignalHandler\0\0AllQuit()\0MainQuit()\0"
    "msg\0ConsoleMsg(QString)\0TimerMainQuit()\0"
};

void MainSignalHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainSignalHandler *_t = static_cast<MainSignalHandler *>(_o);
        switch (_id) {
        case 0: _t->AllQuit(); break;
        case 1: _t->MainQuit(); break;
        case 2: _t->ConsoleMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->TimerMainQuit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainSignalHandler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainSignalHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MainSignalHandler,
      qt_meta_data_MainSignalHandler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainSignalHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainSignalHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainSignalHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainSignalHandler))
        return static_cast<void*>(const_cast< MainSignalHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int MainSignalHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MainSignalHandler::AllQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainSignalHandler::MainQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE