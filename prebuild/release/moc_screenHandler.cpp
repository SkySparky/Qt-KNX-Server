/****************************************************************************
** Meta object code from reading C++ file 'screenHandler.h'
**
** Created: Tue 3. Apr 20:58:30 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../screenHandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screenHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScreenHandler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   15,   14,   14, 0x05,
      72,   50,   14,   14, 0x05,
     114,   92,   14,   14, 0x05,
     180,  165,   14,   14, 0x25,
     211,   92,   14,   14, 0x05,
     262,  165,   14,   14, 0x25,
     293,  165,   14,   14, 0x05,
     349,  330,   14,   14, 0x05,
     379,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     399,   14,   14,   14, 0x0a,
     437,  408,   14,   14, 0x0a,
     474,  461,   14,   14, 0x2a,
     499,  494,   14,   14, 0x0a,
     550,  522,   14,   14, 0x0a,
     632,  611,   14,   14, 0x2a,
     682,  673,   14,   14, 0x0a,
     707,  701,   14,   14, 0x0a,
     756,   50,   14,   14, 0x0a,
     778,   50,   14,   14, 0x0a,
     803,   14,   14,   14, 0x0a,
     823,   14,   14,   14, 0x0a,
     847,   14,   14,   14, 0x0a,
     871,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScreenHandler[] = {
    "ScreenHandler\0\0title,msg\0"
    "SendMsg(QString,QString)\0notifyType,notifyData\0"
    "Notify(int,QString)\0groupAddr,data,action\0"
    "sendDataToKnx(QString,QString,cEMI::en_cemiAction)\0"
    "groupAddr,data\0sendDataToKnx(QString,QString)\0"
    "sendDataToUdp(QString,QString,cEMI::en_cemiAction)\0"
    "sendDataToUdp(QString,QString)\0"
    "sendDataToScreenObj(QString,QString)\0"
    "description,ipAddr\0foundGateway(QString,QString)\0"
    "disconnectGateway()\0onQuit()\0"
    "wantedScreen,wantedSubScreen\0"
    "onScreenChange(int,int)\0wantedScreen\0"
    "onScreenChange(int)\0data\0"
    "onDataFromKnx(QString)\0"
    "type,groupAddr,value,action\0"
    "onDataFromScreenObj(int,QString,QString,cEMI::en_cemiAction)\0"
    "type,groupAddr,value\0"
    "onDataFromScreenObj(int,QString,QString)\0"
    "type,msg\0onMsg(int,QString)\0state\0"
    "onKnxStateChange(KnxGateway::en_knxGatewayState)\0"
    "onNotify(int,QString)\0onKnxNotify(int,QString)\0"
    "onAutosearchTimer()\0onImportReplyFinished()\0"
    "onExportReplyFinished()\0onConnectTimer()\0"
};

void ScreenHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScreenHandler *_t = static_cast<ScreenHandler *>(_o);
        switch (_id) {
        case 0: _t->SendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->Notify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->sendDataToKnx((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< cEMI::en_cemiAction(*)>(_a[3]))); break;
        case 3: _t->sendDataToKnx((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->sendDataToUdp((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< cEMI::en_cemiAction(*)>(_a[3]))); break;
        case 5: _t->sendDataToUdp((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->sendDataToScreenObj((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->foundGateway((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->disconnectGateway(); break;
        case 9: _t->onQuit(); break;
        case 10: _t->onScreenChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->onScreenChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->onDataFromKnx((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->onDataFromScreenObj((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< cEMI::en_cemiAction(*)>(_a[4]))); break;
        case 14: _t->onDataFromScreenObj((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 15: _t->onMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->onKnxStateChange((*reinterpret_cast< KnxGateway::en_knxGatewayState(*)>(_a[1]))); break;
        case 17: _t->onNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: _t->onKnxNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 19: _t->onAutosearchTimer(); break;
        case 20: _t->onImportReplyFinished(); break;
        case 21: _t->onExportReplyFinished(); break;
        case 22: _t->onConnectTimer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ScreenHandler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScreenHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScreenHandler,
      qt_meta_data_ScreenHandler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScreenHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScreenHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScreenHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenHandler))
        return static_cast<void*>(const_cast< ScreenHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int ScreenHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void ScreenHandler::SendMsg(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScreenHandler::Notify(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScreenHandler::sendDataToKnx(QString _t1, QString _t2, cEMI::en_cemiAction _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void ScreenHandler::sendDataToUdp(QString _t1, QString _t2, cEMI::en_cemiAction _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 6
void ScreenHandler::sendDataToScreenObj(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ScreenHandler::foundGateway(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ScreenHandler::disconnectGateway()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE
