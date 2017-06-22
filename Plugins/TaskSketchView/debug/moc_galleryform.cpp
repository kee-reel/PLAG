/****************************************************************************
** Meta object code from reading C++ file 'galleryform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../galleryform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'galleryform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GalleryForm_t {
    QByteArrayData data[10];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GalleryForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GalleryForm_t qt_meta_stringdata_GalleryForm = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GalleryForm"
QT_MOC_LITERAL(1, 12, 12), // "OnItemDelete"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "index"
QT_MOC_LITERAL(4, 32, 13), // "OnItemConvert"
QT_MOC_LITERAL(5, 46, 14), // "OnItemSelected"
QT_MOC_LITERAL(6, 61, 12), // "GalleryItem*"
QT_MOC_LITERAL(7, 74, 4), // "item"
QT_MOC_LITERAL(8, 79, 23), // "on_buttonDelete_clicked"
QT_MOC_LITERAL(9, 103, 30) // "on_buttonConvertToTask_clicked"

    },
    "GalleryForm\0OnItemDelete\0\0index\0"
    "OnItemConvert\0OnItemSelected\0GalleryItem*\0"
    "item\0on_buttonDelete_clicked\0"
    "on_buttonConvertToTask_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GalleryForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   45,    2, 0x08 /* Private */,
       8,    0,   48,    2, 0x08 /* Private */,
       9,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GalleryForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GalleryForm *_t = static_cast<GalleryForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnItemDelete((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OnItemConvert((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->OnItemSelected((*reinterpret_cast< GalleryItem*(*)>(_a[1]))); break;
        case 3: _t->on_buttonDelete_clicked(); break;
        case 4: _t->on_buttonConvertToTask_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GalleryItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GalleryForm::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GalleryForm::OnItemDelete)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GalleryForm::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GalleryForm::OnItemConvert)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GalleryForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GalleryForm.data,
      qt_meta_data_GalleryForm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GalleryForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GalleryForm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GalleryForm.stringdata0))
        return static_cast<void*>(const_cast< GalleryForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int GalleryForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void GalleryForm::OnItemDelete(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GalleryForm::OnItemConvert(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
