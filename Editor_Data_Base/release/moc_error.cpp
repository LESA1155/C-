/****************************************************************************
** Meta object code from reading C++ file 'error.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../error.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'error.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Error_t {
    QByteArrayData data[22];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Error_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Error_t qt_meta_stringdata_Error = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Error"
QT_MOC_LITERAL(1, 6, 10), // "wasDeleted"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 6), // "Error*"
QT_MOC_LITERAL(4, 25, 9), // "errorEdit"
QT_MOC_LITERAL(5, 35, 12), // "deleteFromDB"
QT_MOC_LITERAL(6, 48, 12), // "updateDevice"
QT_MOC_LITERAL(7, 61, 10), // "updateUnit"
QT_MOC_LITERAL(8, 72, 15), // "updateErrorCode"
QT_MOC_LITERAL(9, 88, 15), // "updateErrorText"
QT_MOC_LITERAL(10, 104, 18), // "updateSelectByBits"
QT_MOC_LITERAL(11, 123, 9), // "fillUnits"
QT_MOC_LITERAL(12, 133, 18), // "fillDefectiveUnits"
QT_MOC_LITERAL(13, 152, 19), // "updateDefectiveUnit"
QT_MOC_LITERAL(14, 172, 8), // "slotSave"
QT_MOC_LITERAL(15, 181, 11), // "eventFilter"
QT_MOC_LITERAL(16, 193, 6), // "target"
QT_MOC_LITERAL(17, 200, 7), // "QEvent*"
QT_MOC_LITERAL(18, 208, 5), // "event"
QT_MOC_LITERAL(19, 214, 12), // "slotUpdateCB"
QT_MOC_LITERAL(20, 227, 11), // "fillDevices"
QT_MOC_LITERAL(21, 239, 27) // "changeErrorTextForErrorCode"

    },
    "Error\0wasDeleted\0\0Error*\0errorEdit\0"
    "deleteFromDB\0updateDevice\0updateUnit\0"
    "updateErrorCode\0updateErrorText\0"
    "updateSelectByBits\0fillUnits\0"
    "fillDefectiveUnits\0updateDefectiveUnit\0"
    "slotSave\0eventFilter\0target\0QEvent*\0"
    "event\0slotUpdateCB\0fillDevices\0"
    "changeErrorTextForErrorCode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Error[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   92,    2, 0x0a /* Public */,
       6,    0,   93,    2, 0x0a /* Public */,
       7,    0,   94,    2, 0x0a /* Public */,
       8,    0,   95,    2, 0x0a /* Public */,
       9,    0,   96,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    2,  102,    2, 0x0a /* Public */,
      19,    0,  107,    2, 0x0a /* Public */,
      20,    0,  108,    2, 0x0a /* Public */,
      21,    0,  109,    2, 0x0a /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 17,   16,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Error::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Error *_t = static_cast<Error *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->wasDeleted((*reinterpret_cast< Error*(*)>(_a[1]))); break;
        case 1: _t->deleteFromDB(); break;
        case 2: _t->updateDevice(); break;
        case 3: _t->updateUnit(); break;
        case 4: _t->updateErrorCode(); break;
        case 5: _t->updateErrorText(); break;
        case 6: _t->updateSelectByBits(); break;
        case 7: _t->fillUnits(); break;
        case 8: _t->fillDefectiveUnits(); break;
        case 9: _t->updateDefectiveUnit(); break;
        case 10: _t->slotSave(); break;
        case 11: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->slotUpdateCB(); break;
        case 13: _t->fillDevices(); break;
        case 14: _t->changeErrorTextForErrorCode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Error* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Error::*_t)(Error * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Error::wasDeleted)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Error::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_Error.data,
      qt_meta_data_Error,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Error::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Error::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Error.stringdata0))
        return static_cast<void*>(this);
    return QGroupBox::qt_metacast(_clname);
}

int Error::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Error::wasDeleted(Error * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
