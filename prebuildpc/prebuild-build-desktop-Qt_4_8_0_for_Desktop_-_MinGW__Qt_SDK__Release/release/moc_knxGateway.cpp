/****************************************************************************
** Meta object code from reading C++ file 'knxGateway.h'
**
** Created: Sat 18. Feb 11:04:20 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../prebuildpc/knxGateway.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'knxGateway.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KnxGateway[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x05,
      56,   36,   11,   11, 0x05,
      85,   75,   11,   11, 0x05,
     110,   98,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     132,  127,   11,   11, 0x0a,
     147,   11,   11,   11, 0x0a,
     159,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_KnxGateway[] = {
    "KnxGateway\0\0evtData\0Output(QString)\0"
    "socketError,message\0error(int,QString)\0"
    "logString\0Log(QString)\0msgType,msg\0"
    "Msg(int,QString)\0data\0Input(QString)\0"
    "UdpThread()\0AllQuit()\0"
};

const QMetaObject KnxGateway::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KnxGateway,
      qt_meta_data_KnxGateway, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KnxGateway::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KnxGateway::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KnxGateway::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KnxGateway))
        return static_cast<void*>(const_cast< KnxGateway*>(this));
    return QObject::qt_metacast(_clname);
}

int KnxGateway::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Output((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: Log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: Msg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: Input((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: UdpThread(); break;
        case 6: AllQuit(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void KnxGateway::Output(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KnxGateway::error(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KnxGateway::Log(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void KnxGateway::Msg(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
