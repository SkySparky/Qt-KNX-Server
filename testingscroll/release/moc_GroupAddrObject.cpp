/****************************************************************************
** Meta object code from reading C++ file 'GroupAddrObject.h'
**
** Created: Mon 13. Feb 14:58:33 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GroupAddrObject.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GroupAddrObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GroupAddrObject[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       5,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      31,   16,   16,   16, 0x05,
      52,   16,   16,   16, 0x05,
      71,   16,   16,   16, 0x05,
      86,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     105,  100,   16,   16, 0x0a,
     130,  118,   16,   16, 0x0a,
     164,  154,   16,   16, 0x0a,
     192,  186,   16,   16, 0x0a,
     215,  210,   16,   16, 0x0a,

 // properties: name, type, flags
     100,  232, 0x02495103,
     118,  236, 0x0a495103,
     154,  236, 0x0a495103,
     186,  236, 0x0a495103,
     210,  236, 0x0a495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

static const char qt_meta_stringdata_GroupAddrObject[] = {
    "GroupAddrObject\0\0typeChanged()\0"
    "descriptionChanged()\0groupAddrChanged()\0"
    "valueChanged()\0tagsChanged()\0type\0"
    "setType(int)\0description\0"
    "setDescription(QString)\0groupAddr\0"
    "setGroupAddr(QString)\0value\0"
    "setValue(QString)\0tags\0setTags(QString)\0"
    "int\0QString\0"
};

void GroupAddrObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GroupAddrObject *_t = static_cast<GroupAddrObject *>(_o);
        switch (_id) {
        case 0: _t->typeChanged(); break;
        case 1: _t->descriptionChanged(); break;
        case 2: _t->groupAddrChanged(); break;
        case 3: _t->valueChanged(); break;
        case 4: _t->tagsChanged(); break;
        case 5: _t->setType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setDescription((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setGroupAddr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->setTags((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GroupAddrObject::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GroupAddrObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GroupAddrObject,
      qt_meta_data_GroupAddrObject, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GroupAddrObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GroupAddrObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GroupAddrObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GroupAddrObject))
        return static_cast<void*>(const_cast< GroupAddrObject*>(this));
    return QObject::qt_metacast(_clname);
}

int GroupAddrObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = type(); break;
        case 1: *reinterpret_cast< QString*>(_v) = description(); break;
        case 2: *reinterpret_cast< QString*>(_v) = groupAddr(); break;
        case 3: *reinterpret_cast< QString*>(_v) = value(); break;
        case 4: *reinterpret_cast< QString*>(_v) = tags(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setType(*reinterpret_cast< int*>(_v)); break;
        case 1: setDescription(*reinterpret_cast< QString*>(_v)); break;
        case 2: setGroupAddr(*reinterpret_cast< QString*>(_v)); break;
        case 3: setValue(*reinterpret_cast< QString*>(_v)); break;
        case 4: setTags(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GroupAddrObject::typeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GroupAddrObject::descriptionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GroupAddrObject::groupAddrChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GroupAddrObject::valueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void GroupAddrObject::tagsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
