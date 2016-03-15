/****************************************************************************
** Meta object code from reading C++ file 'screenHandler.h'
**
** Created: Sat 18. Feb 11:04:18 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../prebuildpc/screenHandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screenHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScreenHandler[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x05,
      58,   43,   14,   14, 0x05,
      95,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     115,   14,   14,   14, 0x0a,
     153,  124,   14,   14, 0x0a,
     190,  177,   14,   14, 0x2a,
     210,   15,   14,   14, 0x0a,
     254,  233,   14,   14, 0x0a,
     304,  295,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScreenHandler[] = {
    "ScreenHandler\0\0data\0sendDataToKnx(QString)\0"
    "groupAddr,data\0sendDataToScreenObj(QString,QString)\0"
    "disconnectGateway()\0onQuit()\0"
    "wantedScreen,wantedSubScreen\0"
    "onScreenChange(int,int)\0wantedScreen\0"
    "onScreenChange(int)\0onDataFromKnx(QString)\0"
    "type,groupAddr,value\0"
    "onDataFromScreenObj(int,QString,QString)\0"
    "type,msg\0onMsg(int,QString)\0"
};

const QMetaObject ScreenHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScreenHandler,
      qt_meta_data_ScreenHandler, 0 }
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
        switch (_id) {
        case 0: sendDataToKnx((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: sendDataToScreenObj((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: disconnectGateway(); break;
        case 3: onQuit(); break;
        case 4: onScreenChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: onScreenChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: onDataFromKnx((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: onDataFromScreenObj((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 8: onMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ScreenHandler::sendDataToKnx(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScreenHandler::sendDataToScreenObj(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScreenHandler::disconnectGateway()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
