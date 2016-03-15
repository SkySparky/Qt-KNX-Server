/****************************************************************************
** Meta object code from reading C++ file 'backstage.h'
**
** Created: Mon 2. Apr 20:09:59 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../backstage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backstage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Backstage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      38,   11,   10,   10, 0x05,
     113,   93,   10,   10, 0x25,
     170,  148,   10,   10, 0x05,
     207,  190,   10,   10, 0x05,
     221,   10,   10,   10, 0x05,
     241,  228,   10,   10, 0x05,
     280,  270,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     322,  307,   10,   10, 0x0a,
     353,  148,   10,   10, 0x0a,
     375,  148,   10,   10, 0x0a,
     400,  270,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Backstage[] = {
    "Backstage\0\0type,groupAddr,data,action\0"
    "sendDataToKnx(int,QString,QString,cEMI::en_cemiAction)\0"
    "type,groupAddr,data\0"
    "sendDataToKnx(int,QString,QString)\0"
    "notifyType,notifyData\0Notify(int,QString)\0"
    "screen,subscreen\0exit(int,int)\0quit()\0"
    "cmdtype,data\0qmlNotify(QVariant,QVariant)\0"
    "title,msg\0SendMsg(QVariant,QVariant)\0"
    "groupAddr,data\0onDataFromKnx(QString,QString)\0"
    "onNotify(int,QString)\0onQmlNotify(int,QString)\0"
    "onMsg(QString,QString)\0"
};

void Backstage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Backstage *_t = static_cast<Backstage *>(_o);
        switch (_id) {
        case 0: _t->sendDataToKnx((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< cEMI::en_cemiAction(*)>(_a[4]))); break;
        case 1: _t->sendDataToKnx((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->Notify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->exit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->quit(); break;
        case 5: _t->qmlNotify((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 6: _t->SendMsg((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 7: _t->onDataFromKnx((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->onNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->onQmlNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->onMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Backstage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Backstage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Backstage,
      qt_meta_data_Backstage, &staticMetaObjectExtraData }
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Backstage::sendDataToKnx(int _t1, QString _t2, QString _t3, cEMI::en_cemiAction _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void Backstage::Notify(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Backstage::exit(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Backstage::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Backstage::qmlNotify(QVariant _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Backstage::SendMsg(QVariant _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
