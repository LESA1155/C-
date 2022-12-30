/****************************************************************************
** Meta object code from reading C++ file 'redirectmsg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../redirectmsg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'redirectmsg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RedirectMsg_t {
    QByteArrayData data[14];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RedirectMsg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RedirectMsg_t qt_meta_stringdata_RedirectMsg = {
    {
QT_MOC_LITERAL(0, 0, 11), // "RedirectMsg"
QT_MOC_LITERAL(1, 12, 10), // "wasDeleted"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "RedirectMsg*"
QT_MOC_LITERAL(4, 37, 6), // "redMsg"
QT_MOC_LITERAL(5, 44, 17), // "slotUpdateMsgText"
QT_MOC_LITERAL(6, 62, 12), // "deleteFromDB"
QT_MOC_LITERAL(7, 75, 26), // "updateBeforeDeviceComboBox"
QT_MOC_LITERAL(8, 102, 25), // "updateAfterDeviceComboBox"
QT_MOC_LITERAL(9, 128, 8), // "slotSave"
QT_MOC_LITERAL(10, 137, 11), // "eventFilter"
QT_MOC_LITERAL(11, 149, 6), // "target"
QT_MOC_LITERAL(12, 156, 7), // "QEvent*"
QT_MOC_LITERAL(13, 164, 5) // "event"

    },
    "RedirectMsg\0wasDeleted\0\0RedirectMsg*\0"
    "redMsg\0slotUpdateMsgText\0deleteFromDB\0"
    "updateBeforeDeviceComboBox\0"
    "updateAfterDeviceComboBox\0slotSave\0"
    "eventFilter\0target\0QEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RedirectMsg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,
       9,    0,   56,    2, 0x08 /* Private */,
      10,    2,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 12,   11,   13,

       0        // eod
};

void RedirectMsg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RedirectMsg *_t = static_cast<RedirectMsg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->wasDeleted((*reinterpret_cast< RedirectMsg*(*)>(_a[1]))); break;
        case 1: _t->slotUpdateMsgText(); break;
        case 2: _t->deleteFromDB(); break;
        case 3: _t->updateBeforeDeviceComboBox(); break;
        case 4: _t->updateAfterDeviceComboBox(); break;
        case 5: _t->slotSave(); break;
        case 6: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
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
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RedirectMsg* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (RedirectMsg::*_t)(RedirectMsg * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RedirectMsg::wasDeleted)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject RedirectMsg::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_RedirectMsg.data,
      qt_meta_data_RedirectMsg,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RedirectMsg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RedirectMsg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RedirectMsg.stringdata0))
        return static_cast<void*>(this);
    return QGroupBox::qt_metacast(_clname);
}

int RedirectMsg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void RedirectMsg::wasDeleted(RedirectMsg * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
