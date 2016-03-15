/****************************************************************************
** Meta object code from reading C++ file 'knxServer.h'
**
** Created: Sun 19. Feb 20:36:20 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../knxServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'knxServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KnxServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   11,   10,   10, 0x05,
      64,   55,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   10,   10,   10, 0x0a,
     111,   10,   10,   10, 0x0a,
     169,  146,   10,   10, 0x0a,
     214,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_KnxServer[] = {
    "KnxServer\0\0groupAddr,data\0"
    "GatewayData(QString,QString)\0func,msg\0"
    "Log(QString,QString)\0processPendingDatagrams()\0"
    "processPendingMulticastDatagrams()\0"
    "phyAddr,groupAddr,data\0"
    "onSendDataToClients(QString,QString,QString)\0"
    "onTestTimer()\0"
};

void KnxServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KnxServer *_t = static_cast<KnxServer *>(_o);
        switch (_id) {
        case 0: _t->GatewayData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->Log((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->processPendingDatagrams(); break;
        case 3: _t->processPendingMulticastDatagrams(); break;
        case 4: _t->onSendDataToClients((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->onTestTimer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData KnxServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KnxServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KnxServer,
      qt_meta_data_KnxServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KnxServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KnxServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KnxServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KnxServer))
        return static_cast<void*>(const_cast< KnxServer*>(this));
    return QObject::qt_metacast(_clname);
}

int KnxServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void KnxServer::GatewayData(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KnxServer::Log(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
