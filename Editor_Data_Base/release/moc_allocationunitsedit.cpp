/****************************************************************************
** Meta object code from reading C++ file 'allocationunitsedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../allocationunitsedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'allocationunitsedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AllocationUnitsEdit_t {
    QByteArrayData data[19];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AllocationUnitsEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AllocationUnitsEdit_t qt_meta_stringdata_AllocationUnitsEdit = {
    {
QT_MOC_LITERAL(0, 0, 19), // "AllocationUnitsEdit"
QT_MOC_LITERAL(1, 20, 10), // "wasDeleted"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 20), // "AllocationUnitsEdit*"
QT_MOC_LITERAL(4, 53, 13), // "allocUnitEdit"
QT_MOC_LITERAL(5, 67, 12), // "deleteFromDB"
QT_MOC_LITERAL(6, 80, 18), // "updateComboDevices"
QT_MOC_LITERAL(7, 99, 15), // "updateComboUnit"
QT_MOC_LITERAL(8, 115, 12), // "updateIsMain"
QT_MOC_LITERAL(9, 128, 14), // "updateIsHidden"
QT_MOC_LITERAL(10, 143, 11), // "updateSlots"
QT_MOC_LITERAL(11, 155, 8), // "slotSave"
QT_MOC_LITERAL(12, 164, 11), // "eventFilter"
QT_MOC_LITERAL(13, 176, 6), // "target"
QT_MOC_LITERAL(14, 183, 7), // "QEvent*"
QT_MOC_LITERAL(15, 191, 5), // "event"
QT_MOC_LITERAL(16, 197, 19), // "fillDevicesComboBox"
QT_MOC_LITERAL(17, 217, 17), // "fillUnitsComboBox"
QT_MOC_LITERAL(18, 235, 6) // "slotUp"

    },
    "AllocationUnitsEdit\0wasDeleted\0\0"
    "AllocationUnitsEdit*\0allocUnitEdit\0"
    "deleteFromDB\0updateComboDevices\0"
    "updateComboUnit\0updateIsMain\0"
    "updateIsHidden\0updateSlots\0slotSave\0"
    "eventFilter\0target\0QEvent*\0event\0"
    "fillDevicesComboBox\0fillUnitsComboBox\0"
    "slotUp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AllocationUnitsEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    2,   84,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,
      17,    0,   90,    2, 0x08 /* Private */,
      18,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 14,   13,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AllocationUnitsEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AllocationUnitsEdit *_t = static_cast<AllocationUnitsEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->wasDeleted((*reinterpret_cast< AllocationUnitsEdit*(*)>(_a[1]))); break;
        case 1: _t->deleteFromDB(); break;
        case 2: _t->updateComboDevices(); break;
        case 3: _t->updateComboUnit(); break;
        case 4: _t->updateIsMain(); break;
        case 5: _t->updateIsHidden(); break;
        case 6: _t->updateSlots(); break;
        case 7: _t->slotSave(); break;
        case 8: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->fillDevicesComboBox(); break;
        case 10: _t->fillUnitsComboBox(); break;
        case 11: _t->slotUp(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AllocationUnitsEdit* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (AllocationUnitsEdit::*_t)(AllocationUnitsEdit * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AllocationUnitsEdit::wasDeleted)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject AllocationUnitsEdit::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_AllocationUnitsEdit.data,
      qt_meta_data_AllocationUnitsEdit,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AllocationUnitsEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AllocationUnitsEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AllocationUnitsEdit.stringdata0))
        return static_cast<void*>(this);
    return QGroupBox::qt_metacast(_clname);
}

int AllocationUnitsEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void AllocationUnitsEdit::wasDeleted(AllocationUnitsEdit * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
