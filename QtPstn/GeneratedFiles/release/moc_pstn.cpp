/****************************************************************************
** Meta object code from reading C++ file 'pstn.h'
**
** Created: Fri 9. Mar 23:05:17 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pstn.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pstn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PSTN[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,    5,    5,    5, 0x0a,
      40,    5,    5,    5, 0x0a,
      54,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PSTN[] = {
    "PSTN\0\0OutputLog(QString)\0Input(QString)\0"
    "pstnHandler()\0LocalTimer()\0"
};

void PSTN::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PSTN *_t = static_cast<PSTN *>(_o);
        switch (_id) {
        case 0: _t->OutputLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->Input((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->pstnHandler(); break;
        case 3: _t->LocalTimer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PSTN::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PSTN::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PSTN,
      qt_meta_data_PSTN, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PSTN::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PSTN::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PSTN::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PSTN))
        return static_cast<void*>(const_cast< PSTN*>(this));
    return QObject::qt_metacast(_clname);
}

int PSTN::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PSTN::OutputLog(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
