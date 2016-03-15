/****************************************************************************
** Meta object code from reading C++ file 'GroupAddrObject.h'
**
** Created: Sat 18. Feb 11:04:19 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../prebuildpc/GroupAddrObject.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GroupAddrObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GroupAddrObject[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       8,   94, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      32,   16,   16,   16, 0x05,
      46,   16,   16,   16, 0x05,
      67,   16,   16,   16, 0x05,
      86,   16,   16,   16, 0x05,
     106,   16,   16,   16, 0x05,
     121,   16,   16,   16, 0x05,
     135,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     155,  149,   16,   16, 0x0a,
     174,  169,   16,   16, 0x0a,
     199,  187,   16,   16, 0x0a,
     233,  223,   16,   16, 0x0a,
     266,  255,   16,   16, 0x0a,
     295,  289,   16,   16, 0x0a,
     318,  313,   16,   16, 0x0a,
     340,  335,   16,   16, 0x0a,

 // properties: name, type, flags
     149,  353, 0x02495103,
     169,  353, 0x02495103,
     187,  357, 0x0a495103,
     223,  357, 0x0a495103,
     255,  357, 0x0a495103,
     289,  357, 0x0a495103,
     313,  357, 0x0a495103,
     335,  353, 0x02495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,

       0        // eod
};

static const char qt_meta_stringdata_GroupAddrObject[] = {
    "GroupAddrObject\0\0indexChanged()\0"
    "typeChanged()\0descriptionChanged()\0"
    "groupAddrChanged()\0statusAddrChanged()\0"
    "valueChanged()\0tagsChanged()\0rootChanged()\0"
    "index\0setIndex(int)\0type\0setType(int)\0"
    "description\0setDescription(QString)\0"
    "groupAddr\0setGroupAddr(QString)\0"
    "statusAddr\0setStatusAddr(QString)\0"
    "value\0setValue(QString)\0tags\0"
    "setTags(QString)\0root\0setRoot(int)\0"
    "int\0QString\0"
};

const QMetaObject GroupAddrObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GroupAddrObject,
      qt_meta_data_GroupAddrObject, 0 }
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
        switch (_id) {
        case 0: indexChanged(); break;
        case 1: typeChanged(); break;
        case 2: descriptionChanged(); break;
        case 3: groupAddrChanged(); break;
        case 4: statusAddrChanged(); break;
        case 5: valueChanged(); break;
        case 6: tagsChanged(); break;
        case 7: rootChanged(); break;
        case 8: setIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: setType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: setDescription((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: setGroupAddr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: setStatusAddr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: setValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: setTags((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: setRoot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 16;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = index(); break;
        case 1: *reinterpret_cast< int*>(_v) = type(); break;
        case 2: *reinterpret_cast< QString*>(_v) = description(); break;
        case 3: *reinterpret_cast< QString*>(_v) = groupAddr(); break;
        case 4: *reinterpret_cast< QString*>(_v) = statusAddr(); break;
        case 5: *reinterpret_cast< QString*>(_v) = value(); break;
        case 6: *reinterpret_cast< QString*>(_v) = tags(); break;
        case 7: *reinterpret_cast< int*>(_v) = root(); break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setIndex(*reinterpret_cast< int*>(_v)); break;
        case 1: setType(*reinterpret_cast< int*>(_v)); break;
        case 2: setDescription(*reinterpret_cast< QString*>(_v)); break;
        case 3: setGroupAddr(*reinterpret_cast< QString*>(_v)); break;
        case 4: setStatusAddr(*reinterpret_cast< QString*>(_v)); break;
        case 5: setValue(*reinterpret_cast< QString*>(_v)); break;
        case 6: setTags(*reinterpret_cast< QString*>(_v)); break;
        case 7: setRoot(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GroupAddrObject::indexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GroupAddrObject::typeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GroupAddrObject::descriptionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GroupAddrObject::groupAddrChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void GroupAddrObject::statusAddrChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void GroupAddrObject::valueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void GroupAddrObject::tagsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void GroupAddrObject::rootChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
QT_END_MOC_NAMESPACE
