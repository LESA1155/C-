/****************************************************************************
** Meta object code from reading C++ file 'unitdep.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../unitdep.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'unitdep.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UnitDep_t {
    QByteArrayData data[17];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UnitDep_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UnitDep_t qt_meta_stringdata_UnitDep = {
    {
QT_MOC_LITERAL(0, 0, 7), // "UnitDep"
QT_MOC_LITERAL(1, 8, 10), // "wasDeleted"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "UnitDep*"
QT_MOC_LITERAL(4, 29, 4), // "unit"
QT_MOC_LITERAL(5, 34, 12), // "deleteFromDB"
QT_MOC_LITERAL(6, 47, 14), // "setNewUnitName"
QT_MOC_LITERAL(7, 62, 2), // "id"
QT_MOC_LITERAL(8, 65, 4), // "name"
QT_MOC_LITERAL(9, 70, 11), // "eventFilter"
QT_MOC_LITERAL(10, 82, 6), // "target"
QT_MOC_LITERAL(11, 89, 7), // "QEvent*"
QT_MOC_LITERAL(12, 97, 5), // "event"
QT_MOC_LITERAL(13, 103, 10), // "updateUnit"
QT_MOC_LITERAL(14, 114, 10), // "updateSlot"
QT_MOC_LITERAL(15, 125, 14), // "updateIsHidden"
QT_MOC_LITERAL(16, 140, 8) // "slotSave"

    },
    "UnitDep\0wasDeleted\0\0UnitDep*\0unit\0"
    "deleteFromDB\0setNewUnitName\0id\0name\0"
    "eventFilter\0target\0QEvent*\0event\0"
    "updateUnit\0updateSlot\0updateIsHidden\0"
    "slotSave"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UnitDep[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   57,    2, 0x0a /* Public */,
       6,    2,   58,    2, 0x0a /* Public */,
       9,    2,   63,    2, 0x0a /* Public */,
      13,    0,   68,    2, 0x08 /* Private */,
      14,    0,   69,    2, 0x08 /* Private */,
      15,    0,   70,    2, 0x08 /* Private */,
      16,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    7,    8,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 11,   10,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UnitDep::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UnitDep *_t = static_cast<UnitDep *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->wasDeleted((*reinterpret_cast< UnitDep*(*)>(_a[1]))); break;
        case 1: _t->deleteFromDB(); break;
        case 2: _t->setNewUnitName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->updateUnit(); break;
        case 5: _t->updateSlot(); break;
        case 6: _t->updateIsHidden(); break;
        case 7: _t->slotSave(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UnitDep* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (UnitDep::*_t)(UnitDep * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UnitDep::wasDeleted)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject UnitDep::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_UnitDep.data,
      qt_meta_data_UnitDep,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *UnitDep::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UnitDep::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UnitDep.stringdata0))
        return static_cast<void*>(this);
    return QGroupBox::qt_metacast(_clname);
}

int UnitDep::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void UnitDep::wasDeleted(UnitDep * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
