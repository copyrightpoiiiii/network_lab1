/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_widget_t {
    QByteArrayData data[8];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_widget_t qt_meta_stringdata_widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "widget"
QT_MOC_LITERAL(1, 7, 14), // "showFileDialog"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "clickedSlot"
QT_MOC_LITERAL(4, 35, 10), // "slotOutput"
QT_MOC_LITERAL(5, 46, 3), // "out"
QT_MOC_LITERAL(6, 50, 8), // "slotPort"
QT_MOC_LITERAL(7, 59, 6) // "change"

    },
    "widget\0showFileDialog\0\0clickedSlot\0"
    "slotOutput\0out\0slotPort\0change"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showFileDialog(); break;
        case 1: _t->clickedSlot(); break;
        case 2: _t->slotOutput((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotPort(); break;
        case 4: _t->change(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_widget.data,
    qt_meta_data_widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
