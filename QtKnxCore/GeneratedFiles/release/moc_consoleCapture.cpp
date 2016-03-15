/****************************************************************************
** Meta object code from reading C++ file 'consoleCapture.h'
**
** Created: Fri 9. Mar 20:28:36 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../consoleCapture.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'consoleCapture.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConsoleCapture[] = {

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
      26,   16,   15,   15, 0x05,
      43,   39,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      63,   15,   15,   15, 0x08,
      73,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ConsoleCapture[] = {
    "ConsoleCapture\0\0logString\0Log(QString)\0"
    "msg\0ConsoleMsg(QString)\0AllQuit()\0"
    "ReadLoop()\0"
};

void ConsoleCapture::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConsoleCapture *_t = static_cast<ConsoleCapture *>(_o);
        switch (_id) {
        case 0: _t->Log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ConsoleMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->AllQuit(); break;
        case 3: _t->ReadLoop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ConsoleCapture::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConsoleCapture::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ConsoleCapture,
      qt_meta_data_ConsoleCapture, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConsoleCapture::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConsoleCapture::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConsoleCapture::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConsoleCapture))
        return static_cast<void*>(const_cast< ConsoleCapture*>(this));
    return QObject::qt_metacast(_clname);
}

int ConsoleCapture::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ConsoleCapture::Log(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConsoleCapture::ConsoleMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
