/****************************************************************************
** Meta object code from reading C++ file 'spriteeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../spriteeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spriteeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SpriteEditor_t {
    QByteArrayData data[5];
    char stringdata[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpriteEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpriteEditor_t qt_meta_stringdata_SpriteEditor = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SpriteEditor"
QT_MOC_LITERAL(1, 13, 27), // "on_actionOpenFile_triggered"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 31), // "on_listWidget_currentRowChanged"
QT_MOC_LITERAL(4, 74, 32) // "on_pushButton_ClearPoint_clicked"

    },
    "SpriteEditor\0on_actionOpenFile_triggered\0"
    "\0on_listWidget_currentRowChanged\0"
    "on_pushButton_ClearPoint_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpriteEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    1,   30,    2, 0x08 /* Private */,
       4,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void SpriteEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SpriteEditor *_t = static_cast<SpriteEditor *>(_o);
        switch (_id) {
        case 0: _t->on_actionOpenFile_triggered(); break;
        case 1: _t->on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_ClearPoint_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject SpriteEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SpriteEditor.data,
      qt_meta_data_SpriteEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SpriteEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpriteEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SpriteEditor.stringdata))
        return static_cast<void*>(const_cast< SpriteEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SpriteEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
