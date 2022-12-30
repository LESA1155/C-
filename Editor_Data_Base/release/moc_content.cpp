/****************************************************************************
** Meta object code from reading C++ file 'content.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../content.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'content.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Content_t {
    QByteArrayData data[18];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Content_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Content_t qt_meta_stringdata_Content = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Content"
QT_MOC_LITERAL(1, 8, 15), // "unitNameChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 2), // "id"
QT_MOC_LITERAL(4, 28, 4), // "name"
QT_MOC_LITERAL(5, 33, 14), // "setNewUnitName"
QT_MOC_LITERAL(6, 48, 11), // "updateUnits"
QT_MOC_LITERAL(7, 60, 19), // "updateDefectiveUnit"
QT_MOC_LITERAL(8, 80, 5), // "index"
QT_MOC_LITERAL(9, 86, 22), // "updateDefectiveAddUnit"
QT_MOC_LITERAL(10, 109, 6), // "remove"
QT_MOC_LITERAL(11, 116, 8), // "UnitDep*"
QT_MOC_LITERAL(12, 125, 4), // "unit"
QT_MOC_LITERAL(13, 130, 7), // "addUnit"
QT_MOC_LITERAL(14, 138, 11), // "eventFilter"
QT_MOC_LITERAL(15, 150, 6), // "target"
QT_MOC_LITERAL(16, 157, 7), // "QEvent*"
QT_MOC_LITERAL(17, 165, 5) // "event"

    },
    "Content\0unitNameChanged\0\0id\0name\0"
    "setNewUnitName\0updateUnits\0"
    "updateDefectiveUnit\0index\0"
    "updateDefectiveAddUnit\0remove\0UnitDep*\0"
    "unit\0addUnit\0eventFilter\0target\0QEvent*\0"
    "event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Content[] = {

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
       1,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   59,    2, 0x0a /* Public */,
       6,    0,   64,    2, 0x0a /* Public */,
       7,    1,   65,    2, 0x0a /* Public */,
       9,    1,   68,    2, 0x0a /* Public */,
      10,    1,   71,    2, 0x08 /* Private */,
      13,    0,   74,    2, 0x08 /* Private */,
      14,    2,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 16,   15,   17,

       0        // eod
};

void Content::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Content *_t = static_cast<Content *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->unitNameChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->setNewUnitName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->updateUnits(); break;
        case 3: _t->updateDefectiveUnit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateDefectiveAddUnit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->remove((*reinterpret_cast< UnitDep*(*)>(_a[1]))); break;
        case 6: _t->addUnit(); break;
        case 7: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
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
            typedef void (Content::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Content::unitNameChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Content::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Content.data,
      qt_meta_data_Content,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Content::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Content::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Content.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Content::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void Content::unitNameChanged(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
