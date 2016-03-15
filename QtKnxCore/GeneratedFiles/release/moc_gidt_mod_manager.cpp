/****************************************************************************
** Meta object code from reading C++ file 'gidt_mod_manager.h'
**
** Created: Fri 9. Mar 20:28:37 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gidt_mod_manager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gidt_mod_manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModuleManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   15,   14,   14, 0x05,
      38,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   14,   14,   14, 0x0a,
      70,   14,   14,   14, 0x0a,
      85,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ModuleManager[] = {
    "ModuleManager\0\0logString\0Log(QString)\0"
    "Output(QString)\0ManagerThread()\0"
    "Input(QString)\0AllQuit()\0"
};

void ModuleManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuleManager *_t = static_cast<ModuleManager *>(_o);
        switch (_id) {
        case 0: _t->Log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->Output((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ManagerThread(); break;
        case 3: _t->Input((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->AllQuit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModuleManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModuleManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModuleManager,
      qt_meta_data_ModuleManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModuleManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModuleManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModuleManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModuleManager))
        return static_cast<void*>(const_cast< ModuleManager*>(this));
    return QObject::qt_metacast(_clname);
}

int ModuleManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ModuleManager::Log(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModuleManager::Output(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
