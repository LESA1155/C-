/****************************************************************************
** Meta object code from reading C++ file 'unit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../unit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'unit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Unit_t {
    QByteArrayData data[18];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Unit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Unit_t qt_meta_stringdata_Unit = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Unit"
QT_MOC_LITERAL(1, 5, 10), // "wasDeleted"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 5), // "Unit*"
QT_MOC_LITERAL(4, 23, 8), // "unitEdit"
QT_MOC_LITERAL(5, 32, 15), // "unitNameChanged"
QT_MOC_LITERAL(6, 48, 2), // "id"
QT_MOC_LITERAL(7, 51, 4), // "name"
QT_MOC_LITERAL(8, 56, 12), // "deleteFromDB"
QT_MOC_LITERAL(9, 69, 10), // "updateName"
QT_MOC_LITERAL(10, 80, 10), // "updateTest"
QT_MOC_LITERAL(11, 91, 19), // "updateIsOnLocalhost"
QT_MOC_LITERAL(12, 111, 16), // "updateIsAutotest"
QT_MOC_LITERAL(13, 128, 16), // "updateIsBlocking"
QT_MOC_LITERAL(14, 145, 22), // "updateRunOnAnotherNode"
QT_MOC_LITERAL(15, 168, 23), // "updateWaitForAddnetTest"
QT_MOC_LITERAL(16, 192, 11), // "updateSpare"
QT_MOC_LITERAL(17, 204, 8) // "slotSave"

    },
    "Unit\0wasDeleted\0\0Unit*\0unitEdit\0"
    "unitNameChanged\0id\0name\0deleteFromDB\0"
    "updateName\0updateTest\0updateIsOnLocalhost\0"
    "updateIsAutotest\0updateIsBlocking\0"
    "updateRunOnAnotherNode\0updateWaitForAddnetTest\0"
    "updateSpare\0slotSave"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Unit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       5,    2,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   82,    2, 0x08 /* Private */,
       9,    0,   83,    2, 0x08 /* Private */,
      10,    0,   84,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    0,   89,    2, 0x08 /* Private */,
      16,    0,   90,    2, 0x08 /* Private */,
      17,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Unit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Unit *_t = static_cast<Unit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->wasDeleted((*reinterpret_cast< Unit*(*)>(_a[1]))); break;
        case 1: _t->unitNameChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->deleteFromDB(); break;
        case 3: _t->updateName(); break;
        case 4: _t->updateTest(); break;
        case 5: _t->updateIsOnLocalhost(); break;
        case 6: _t->updateIsAutotest(); break;
        case 7: _t->updateIsBlocking(); break;
        case 8: _t->updateRunOnAnotherNode(); break;
        case 9: _t->updateWaitForAddnetTest(); break;
        case 10: _t->updateSpare(); break;
        case 11: _t->slotSave(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Unit* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Unit::*_t)(Unit * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Unit::wasDeleted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Unit::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Unit::unitNameChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Unit::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_Unit.data,
      qt_meta_data_Unit,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Unit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Unit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Unit.stringdata0))
        return static_cast<void*>(this);
    return QGroupBox::qt_metacast(_clname);
}

int Unit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Unit::wasDeleted(Unit * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Unit::unitNameChanged(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
