/****************************************************************************
** Meta object code from reading C++ file 'device.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../device.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'device.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Device_t {
    QByteArrayData data[23];
    char stringdata0[271];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Device_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Device_t qt_meta_stringdata_Device = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Device"
QT_MOC_LITERAL(1, 7, 10), // "wasDeleted"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "Device*"
QT_MOC_LITERAL(4, 27, 10), // "deviceEdit"
QT_MOC_LITERAL(5, 38, 17), // "deviceNameChanged"
QT_MOC_LITERAL(6, 56, 2), // "id"
QT_MOC_LITERAL(7, 59, 4), // "name"
QT_MOC_LITERAL(8, 64, 15), // "unitNameChanged"
QT_MOC_LITERAL(9, 80, 12), // "unitsChanged"
QT_MOC_LITERAL(10, 93, 12), // "deleteFromDB"
QT_MOC_LITERAL(11, 106, 10), // "updateName"
QT_MOC_LITERAL(12, 117, 16), // "updateUseReserve"
QT_MOC_LITERAL(13, 134, 15), // "updateMainTitle"
QT_MOC_LITERAL(14, 150, 20), // "updateMainShortTitle"
QT_MOC_LITERAL(15, 171, 18), // "updateReserveTitle"
QT_MOC_LITERAL(16, 190, 23), // "updateReserveShortTitle"
QT_MOC_LITERAL(17, 214, 14), // "updatePriority"
QT_MOC_LITERAL(18, 229, 8), // "slotSave"
QT_MOC_LITERAL(19, 238, 11), // "eventFilter"
QT_MOC_LITERAL(20, 250, 6), // "target"
QT_MOC_LITERAL(21, 257, 7), // "QEvent*"
QT_MOC_LITERAL(22, 265, 5) // "event"

    },
    "Device\0wasDeleted\0\0Device*\0deviceEdit\0"
    "deviceNameChanged\0id\0name\0unitNameChanged\0"
    "unitsChanged\0deleteFromDB\0updateName\0"
    "updateUseReserve\0updateMainTitle\0"
    "updateMainShortTitle\0updateReserveTitle\0"
    "updateReserveShortTitle\0updatePriority\0"
    "slotSave\0eventFilter\0target\0QEvent*\0"
    "event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Device[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       5,    2,   87,    2, 0x06 /* Public */,
       8,    2,   92,    2, 0x06 /* Public */,
       9,    0,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   98,    2, 0x08 /* Private */,
      11,    0,   99,    2, 0x08 /* Private */,
      12,    0,  100,    2, 0x08 /* Private */,
      13,    0,  101,    2, 0x08 /* Private */,
      14,    0,  102,    2, 0x08 /* Private */,
      15,    0,  103,    2, 0x08 /* Private */,
      16,    0,  104,    2, 0x08 /* Private */,
      17,    0,  105,    2, 0x08 /* Private */,
      18,    0,  106,    2, 0x08 /* Private */,
      19,    2,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    6,    7,
    QMetaType::Void,

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
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 21,   20,   22,

       0        // eod
};

void Device::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Device *_t = static_cast<Device *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->wasDeleted((*reinterpret_cast< Device*(*)>(_a[1]))); break;
        case 1: _t->deviceNameChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->unitNameChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->unitsChanged(); break;
        case 4: _t->deleteFromDB(); break;
        case 5: _t->updateName(); break;
        case 6: _t->updateUseReserve(); break;
        case 7: _t->updateMainTitle(); break;
        case 8: _t->updateMainShortTitle(); break;
        case 9: _t->updateReserveTitle(); break;
        case 10: _t->updateReserveShortTitle(); break;
        case 11: _t->updatePriority(); break;
        case 12: _t->slotSave(); break;
        case 13: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Device* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Device::*_t)(Device * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Device::wasDeleted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Device::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Device::deviceNameChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Device::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Device::unitNameChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Device::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Device::unitsChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Device::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_Device.data,
      qt_meta_data_Device,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Device::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Device::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Device.stringdata0))
        return static_cast<void*>(this);
    return QGroupBox::qt_metacast(_clname);
}

int Device::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Device::wasDeleted(Device * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Device::deviceNameChanged(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Device::unitNameChanged(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Device::unitsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
