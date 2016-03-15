/****************************************************************************
** Meta object code from reading C++ file 'XSocket.h'
**
** Created: Fri 9. Mar 21:25:00 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../XSocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XSocket[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,   28,    8,    8, 0x0a,
      91,   77,    8,    8, 0x2a,
     116,  111,    8,    8, 0x2a,
     131,    8,    8,    8, 0x0a,
     143,    8,    8,    8, 0x0a,
     156,    8,    8,    8, 0x0a,
     171,    8,    8,    8, 0x0a,
     199,  195,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XSocket[] = {
    "XSocket\0\0Output(QByteArray)\0"
    "data,preDelay,postDelay\0"
    "Input(QString,uint,uint)\0data,preDelay\0"
    "Input(QString,uint)\0data\0Input(QString)\0"
    "OnTimeout()\0OnCmdTimer()\0OnClientData()\0"
    "OnClientDisconnection()\0err\0"
    "OnClientError(QAbstractSocket::SocketError)\0"
};

void XSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        XSocket *_t = static_cast<XSocket *>(_o);
        switch (_id) {
        case 0: _t->Output((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->Input((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 2: _t->Input((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 3: _t->Input((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->OnTimeout(); break;
        case 5: _t->OnCmdTimer(); break;
        case 6: _t->OnClientData(); break;
        case 7: _t->OnClientDisconnection(); break;
        case 8: _t->OnClientError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData XSocket::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject XSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XSocket,
      qt_meta_data_XSocket, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XSocket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XSocket))
        return static_cast<void*>(const_cast< XSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int XSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void XSocket::Output(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
