/****************************************************************************
** Meta object code from reading C++ file 'stage.h'
**
** Created: Sat 18. Feb 11:04:14 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../prebuildpc/stage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Stage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,    7,    6,    6, 0x05,
      79,   62,    6,    6, 0x05,
      93,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
     100,    6,    6,    6, 0x0a,
     120,    6,    6,    6, 0x0a,
     133,  129,    6,    6, 0x0a,
     155,    7,    6,    6, 0x0a,
     207,  192,    6,    6, 0x0a,
     245,  238,    6,    6, 0x0a,
     257,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Stage[] = {
    "Stage\0\0type,groupAddr,data\0"
    "sendDataToKnx(int,QString,QString)\0"
    "screen,subscreen\0exit(int,int)\0quit()\0"
    "DisplayMainScreen()\0onBack()\0tag\0"
    "UpdateScreen(QString)\0"
    "onUiValueChange(int,QString,QString)\0"
    "groupAddr,data\0onDataFromKnx(QString,QString)\0"
    "screen\0onExit(int)\0onQuit()\0"
};

const QMetaObject Stage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Stage,
      qt_meta_data_Stage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Stage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Stage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Stage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Stage))
        return static_cast<void*>(const_cast< Stage*>(this));
    return QObject::qt_metacast(_clname);
}

int Stage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendDataToKnx((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: exit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: quit(); break;
        case 3: DisplayMainScreen(); break;
        case 4: onBack(); break;
        case 5: UpdateScreen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: onUiValueChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: onDataFromKnx((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: onExit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: onQuit(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Stage::sendDataToKnx(int _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Stage::exit(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Stage::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
