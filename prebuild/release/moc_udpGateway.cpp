/****************************************************************************
** Meta object code from reading C++ file 'udpGateway.h'
**
** Created: Tue 3. Apr 20:58:31 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../udpGateway.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpGateway.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UdpGateway[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x05,
      47,   41,   11,   11, 0x05,
     110,   88,   11,   11, 0x05,
     150,  130,   11,   11, 0x05,
     179,  169,   11,   11, 0x05,
     204,  192,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     221,   11,   11,   11, 0x0a,
     236,   11,   11,   11, 0x0a,
     248,   11,   11,   11, 0x0a,
     262,   11,   11,   11, 0x0a,
     278,   11,   11,   11, 0x0a,
     309,  287,   11,   11, 0x0a,
     372,  357,   11,   11, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_UdpGateway[] = {
    "UdpGateway\0\0evtData\0DataFromUdp(QString)\0"
    "state\0UdpState(KnxGateway::en_knxGatewayState)\0"
    "notifyType,notifyData\0Notify(int,QString)\0"
    "socketError,message\0error(int,QString)\0"
    "logString\0Log(QString)\0msgType,msg\0"
    "Msg(int,QString)\0onUdpControl()\0"
    "onUdpData()\0onHeartBeat()\0onDataTimeout()\0"
    "onQuit()\0groupAddr,data,action\0"
    "onSendData(QString,QString,cEMI::en_cemiAction)\0"
    "groupAddr,data\0onSendData(QString,QString)\0"
};

void UdpGateway::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UdpGateway *_t = static_cast<UdpGateway *>(_o);
        switch (_id) {
        case 0: _t->DataFromUdp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->UdpState((*reinterpret_cast< KnxGateway::en_knxGatewayState(*)>(_a[1]))); break;
        case 2: _t->Notify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->Log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->Msg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->onUdpControl(); break;
        case 7: _t->onUdpData(); break;
        case 8: _t->onHeartBeat(); break;
        case 9: _t->onDataTimeout(); break;
        case 10: _t->onQuit(); break;
        case 11: _t->onSendData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< cEMI::en_cemiAction(*)>(_a[3]))); break;
        case 12: _t->onSendData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UdpGateway::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UdpGateway::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UdpGateway,
      qt_meta_data_UdpGateway, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UdpGateway::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UdpGateway::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UdpGateway::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UdpGateway))
        return static_cast<void*>(const_cast< UdpGateway*>(this));
    return QObject::qt_metacast(_clname);
}

int UdpGateway::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void UdpGateway::DataFromUdp(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UdpGateway::UdpState(KnxGateway::en_knxGatewayState _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UdpGateway::Notify(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UdpGateway::error(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UdpGateway::Log(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void UdpGateway::Msg(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
