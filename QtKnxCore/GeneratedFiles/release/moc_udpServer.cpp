/****************************************************************************
** Meta object code from reading C++ file 'udpServer.h'
**
** Created: Fri 9. Mar 20:28:44 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../udpServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UdpServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   11,   10,   10, 0x05,
      63,   56,   10,   10, 0x05,
      89,   79,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     102,   10,   10,   10, 0x0a,
     117,   10,   10,   10, 0x0a,
     129,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UdpServer[] = {
    "UdpServer\0\0moduleName,params\0"
    "SendEvent(QString,QString)\0knxCmd\0"
    "Output(QString)\0logString\0Log(QString)\0"
    "Input(QString)\0OnUdpData()\0AllQuit()\0"
};

void UdpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UdpServer *_t = static_cast<UdpServer *>(_o);
        switch (_id) {
        case 0: _t->SendEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->Output((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->Log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->Input((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->OnUdpData(); break;
        case 5: _t->AllQuit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UdpServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UdpServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UdpServer,
      qt_meta_data_UdpServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UdpServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UdpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UdpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UdpServer))
        return static_cast<void*>(const_cast< UdpServer*>(this));
    return QObject::qt_metacast(_clname);
}

int UdpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void UdpServer::SendEvent(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UdpServer::Output(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UdpServer::Log(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
