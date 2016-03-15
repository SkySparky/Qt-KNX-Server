/****************************************************************************
** Meta object code from reading C++ file 'pdxalarm.h'
**
** Created: Fri 9. Mar 21:26:12 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pdxalarm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pdxalarm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PdxAlarm[] = {

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
      13,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,    9,    9,    9, 0x0a,
      54,    9,    9,    9, 0x0a,
      76,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PdxAlarm[] = {
    "PdxAlarm\0\0,,\0Output(QString,uint,uint)\0"
    "Input(QString)\0AlrmInput(QByteArray)\0"
    "CmdTimer()\0"
};

void PdxAlarm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PdxAlarm *_t = static_cast<PdxAlarm *>(_o);
        switch (_id) {
        case 0: _t->Output((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 1: _t->Input((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->AlrmInput((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->CmdTimer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PdxAlarm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PdxAlarm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PdxAlarm,
      qt_meta_data_PdxAlarm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PdxAlarm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PdxAlarm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PdxAlarm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PdxAlarm))
        return static_cast<void*>(const_cast< PdxAlarm*>(this));
    return QObject::qt_metacast(_clname);
}

int PdxAlarm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PdxAlarm::Output(QString _t1, uint _t2, uint _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
