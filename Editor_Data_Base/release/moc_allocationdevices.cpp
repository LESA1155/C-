/****************************************************************************
** Meta object code from reading C++ file 'allocationdevices.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../allocationdevices.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'allocationdevices.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AllocationDevices_t {
    QByteArrayData data[11];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AllocationDevices_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AllocationDevices_t qt_meta_stringdata_AllocationDevices = {
    {
QT_MOC_LITERAL(0, 0, 17), // "AllocationDevices"
QT_MOC_LITERAL(1, 18, 12), // "widthChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "width"
QT_MOC_LITERAL(4, 38, 13), // "heightChanged"
QT_MOC_LITERAL(5, 52, 6), // "height"
QT_MOC_LITERAL(6, 59, 11), // "gridChanged"
QT_MOC_LITERAL(7, 71, 8), // "gridStep"
QT_MOC_LITERAL(8, 80, 17), // "updateWidthWindow"
QT_MOC_LITERAL(9, 98, 18), // "updateHeightWindow"
QT_MOC_LITERAL(10, 117, 14) // "updateGridStep"

    },
    "AllocationDevices\0widthChanged\0\0width\0"
    "heightChanged\0height\0gridChanged\0"
    "gridStep\0updateWidthWindow\0"
    "updateHeightWindow\0updateGridStep"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AllocationDevices[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   53,    2, 0x08 /* Private */,
       9,    0,   54,    2, 0x08 /* Private */,
      10,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AllocationDevices::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AllocationDevices *_t = static_cast<AllocationDevices *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->widthChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->heightChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->gridChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateWidthWindow(); break;
        case 4: _t->updateHeightWindow(); break;
        case 5: _t->updateGridStep(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (AllocationDevices::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AllocationDevices::widthChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AllocationDevices::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AllocationDevices::heightChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AllocationDevices::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AllocationDevices::gridChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject AllocationDevices::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AllocationDevices.data,
      qt_meta_data_AllocationDevices,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AllocationDevices::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AllocationDevices::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AllocationDevices.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AllocationDevices::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void AllocationDevices::widthChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AllocationDevices::heightChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AllocationDevices::gridChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
