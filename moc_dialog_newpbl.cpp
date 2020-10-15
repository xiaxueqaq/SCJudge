/****************************************************************************
** Meta object code from reading C++ file 'dialog_newpbl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../untitled/dialog_newpbl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_newpbl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dialog_newpbl_t {
    QByteArrayData data[12];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dialog_newpbl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dialog_newpbl_t qt_meta_stringdata_dialog_newpbl = {
    {
QT_MOC_LITERAL(0, 0, 13), // "dialog_newpbl"
QT_MOC_LITERAL(1, 14, 6), // "dlgRet"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 22), // "on_radBtn_Trad_clicked"
QT_MOC_LITERAL(4, 45, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(5, 67, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(6, 89, 22), // "on_ckBox_Maple_clicked"
QT_MOC_LITERAL(7, 112, 20), // "on_ckBox_MMA_clicked"
QT_MOC_LITERAL(8, 133, 22), // "on_radBtn_Intr_clicked"
QT_MOC_LITERAL(9, 156, 22), // "on_btn_src_dir_clicked"
QT_MOC_LITERAL(10, 179, 24), // "on_btn_src_dir_2_clicked"
QT_MOC_LITERAL(11, 204, 23) // "on_btn_data_dir_clicked"

    },
    "dialog_newpbl\0dlgRet\0\0on_radBtn_Trad_clicked\0"
    "on_pushButton_clicked\0on_buttonBox_accepted\0"
    "on_ckBox_Maple_clicked\0on_ckBox_MMA_clicked\0"
    "on_radBtn_Intr_clicked\0on_btn_src_dir_clicked\0"
    "on_btn_src_dir_2_clicked\0"
    "on_btn_data_dir_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dialog_newpbl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    8,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   81,    2, 0x08 /* Private */,
       4,    0,   82,    2, 0x08 /* Private */,
       5,    0,   83,    2, 0x08 /* Private */,
       6,    0,   84,    2, 0x08 /* Private */,
       7,    0,   85,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,    2,    2,    2,    2,    2,

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

       0        // eod
};

void dialog_newpbl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<dialog_newpbl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dlgRet((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 1: _t->on_radBtn_Trad_clicked(); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->on_buttonBox_accepted(); break;
        case 4: _t->on_ckBox_Maple_clicked(); break;
        case 5: _t->on_ckBox_MMA_clicked(); break;
        case 6: _t->on_radBtn_Intr_clicked(); break;
        case 7: _t->on_btn_src_dir_clicked(); break;
        case 8: _t->on_btn_src_dir_2_clicked(); break;
        case 9: _t->on_btn_data_dir_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (dialog_newpbl::*)(QString , int , int , QString , QString , QString , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dialog_newpbl::dlgRet)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject dialog_newpbl::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_dialog_newpbl.data,
    qt_meta_data_dialog_newpbl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *dialog_newpbl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dialog_newpbl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dialog_newpbl.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int dialog_newpbl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void dialog_newpbl::dlgRet(QString _t1, int _t2, int _t3, QString _t4, QString _t5, QString _t6, QString _t7, int _t8)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
