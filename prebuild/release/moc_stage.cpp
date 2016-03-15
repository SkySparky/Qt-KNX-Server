/****************************************************************************
** Meta object code from reading C++ file 'stage.h'
**
** Created: Mon 2. Apr 20:10:05 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../stage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Stage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,    7,    6,    6, 0x05,
     109,   89,    6,    6, 0x25,
     166,  144,    6,    6, 0x05,
     203,  186,    6,    6, 0x05,
     217,    6,    6,    6, 0x05,
     234,  224,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
     261,    6,    6,    6, 0x0a,
     296,  281,    6,    6, 0x0a,
     327,  144,    6,    6, 0x0a,
     349,  144,    6,    6, 0x0a,
     374,  224,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Stage[] = {
    "Stage\0\0type,groupAddr,data,action\0"
    "sendDataToKnx(int,QString,QString,cEMI::en_cemiAction)\0"
    "type,groupAddr,data\0"
    "sendDataToKnx(int,QString,QString)\0"
    "notifyType,notifyData\0Notify(int,QString)\0"
    "screen,subscreen\0exit(int,int)\0quit()\0"
    "title,msg\0SendMsg(QVariant,QVariant)\0"
    "DisplayMainScreen()\0groupAddr,data\0"
    "onDataFromKnx(QString,QString)\0"
    "onNotify(int,QString)\0onQmlNotify(int,QString)\0"
    "onMsg(QString,QString)\0"
};

void Stage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Stage *_t = static_cast<Stage *>(_o);
        switch (_id) {
        case 0: _t->sendDataToKnx((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< cEMI::en_cemiAction(*)>(_a[4]))); break;
        case 1: _t->sendDataToKnx((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->Notify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->exit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->quit(); break;
        case 5: _t->SendMsg((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 6: _t->DisplayMainScreen(); break;
        case 7: _t->onDataFromKnx((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->onNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->onQmlNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->onMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Stage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Stage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Stage,
      qt_meta_data_Stage, &staticMetaObjectExtraData }
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Stage::sendDataToKnx(int _t1, QString _t2, QString _t3, cEMI::en_cemiAction _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void Stage::Notify(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Stage::exit(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Stage::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Stage::SendMsg(QVariant _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
