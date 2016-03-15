/****************************************************************************
** Meta object code from reading C++ file 'btnhandler.h'
**
** Created: Mon 13. Feb 14:52:59 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../btnhandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'btnhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BtnHandler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      23,   19,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BtnHandler[] = {
    "BtnHandler\0\0quit()\0btn\0onBtnPressed(QString)\0"
};

void BtnHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BtnHandler *_t = static_cast<BtnHandler *>(_o);
        switch (_id) {
        case 0: _t->quit(); break;
        case 1: _t->onBtnPressed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BtnHandler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BtnHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BtnHandler,
      qt_meta_data_BtnHandler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BtnHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BtnHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BtnHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BtnHandler))
        return static_cast<void*>(const_cast< BtnHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int BtnHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void BtnHandler::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
