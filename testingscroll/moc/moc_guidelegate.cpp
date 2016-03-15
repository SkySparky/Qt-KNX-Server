/****************************************************************************
** Meta object code from reading C++ file 'guidelegate.h'
**
** Created: Sun 12. Feb 20:21:04 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../guidelegate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guidelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GuiDelegate[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   70,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GuiDelegate[] = {
    "GuiDelegate\0\0id,type,data\0"
    "SendSignalToQml(QVariant,QVariant,QVariant)\0"
    "objId,objData\0onDataFromQml(int,QString)\0"
};

const QMetaObject GuiDelegate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GuiDelegate,
      qt_meta_data_GuiDelegate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GuiDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GuiDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GuiDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GuiDelegate))
        return static_cast<void*>(const_cast< GuiDelegate*>(this));
    return QObject::qt_metacast(_clname);
}

int GuiDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SendSignalToQml((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 1: onDataFromQml((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void GuiDelegate::SendSignalToQml(QVariant _t1, QVariant _t2, QVariant _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
