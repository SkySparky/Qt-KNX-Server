/****************************************************************************
** Meta object code from reading C++ file 'backstage.h'
**
** Created: Sat 18. Feb 11:04:13 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../prebuildpc/backstage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backstage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Backstage[] = {

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
      31,   11,   10,   10, 0x05,
      83,   66,   10,   10, 0x05,
      97,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     121,  104,   10,   10, 0x0a,
     152,  146,   10,   10, 0x0a,
     190,  172,   10,   10, 0x0a,
     236,  221,   10,   10, 0x0a,
     274,  267,   10,   10, 0x0a,
     286,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Backstage[] = {
    "Backstage\0\0type,groupAddr,data\0"
    "sendDataToKnx(int,QString,QString)\0"
    "screen,subscreen\0exit(int,int)\0quit()\0"
    "index,deviceData\0onAddDevice(int,QString)\0"
    "index\0onRemoveDevice(int)\0settingName,value\0"
    "onSaveSetting(QString,QString)\0"
    "groupAddr,data\0onDataFromKnx(QString,QString)\0"
    "status\0onExit(int)\0onQuit()\0"
};

const QMetaObject Backstage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Backstage,
      qt_meta_data_Backstage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Backstage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Backstage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Backstage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Backstage))
        return static_cast<void*>(const_cast< Backstage*>(this));
    return QObject::qt_metacast(_clname);
}

int Backstage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendDataToKnx((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: exit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: quit(); break;
        case 3: onAddDevice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: onRemoveDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: onSaveSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: onDataFromKnx((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: onExit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: onQuit(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Backstage::sendDataToKnx(int _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Backstage::exit(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Backstage::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
