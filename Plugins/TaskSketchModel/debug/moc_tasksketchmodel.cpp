/****************************************************************************
** Meta object code from reading C++ file 'tasksketchmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tasksketchmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tasksketchmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TaskSketchModel_t {
    QByteArrayData data[10];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaskSketchModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaskSketchModel_t qt_meta_stringdata_TaskSketchModel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TaskSketchModel"
QT_MOC_LITERAL(1, 16, 7), // "OnClose"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "PluginInfo*"
QT_MOC_LITERAL(4, 37, 5), // "model"
QT_MOC_LITERAL(5, 43, 21), // "ReferencePluginClosed"
QT_MOC_LITERAL(6, 65, 10), // "pluginInfo"
QT_MOC_LITERAL(7, 76, 4), // "Open"
QT_MOC_LITERAL(8, 81, 13), // "IModelPlugin*"
QT_MOC_LITERAL(9, 95, 5) // "Close"

    },
    "TaskSketchModel\0OnClose\0\0PluginInfo*\0"
    "model\0ReferencePluginClosed\0pluginInfo\0"
    "Open\0IModelPlugin*\0Close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskSketchModel[] = {

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
       1,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   43,    2, 0x0a /* Public */,
       7,    1,   46,    2, 0x0a /* Public */,
       9,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    6,
    QMetaType::Bool, 0x80000000 | 8,    4,
    QMetaType::Void,

       0        // eod
};

void TaskSketchModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TaskSketchModel *_t = static_cast<TaskSketchModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnClose((*reinterpret_cast< PluginInfo*(*)>(_a[1]))); break;
        case 1: _t->OnClose(); break;
        case 2: _t->ReferencePluginClosed((*reinterpret_cast< PluginInfo*(*)>(_a[1]))); break;
        case 3: { bool _r = _t->Open((*reinterpret_cast< IModelPlugin*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->Close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TaskSketchModel::*_t)(PluginInfo * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TaskSketchModel::OnClose)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TaskSketchModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TaskSketchModel::OnClose)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject TaskSketchModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TaskSketchModel.data,
      qt_meta_data_TaskSketchModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TaskSketchModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskSketchModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TaskSketchModel.stringdata0))
        return static_cast<void*>(const_cast< TaskSketchModel*>(this));
    if (!strcmp(_clname, "ITaskSketchModel"))
        return static_cast< ITaskSketchModel*>(const_cast< TaskSketchModel*>(this));
    if (!strcmp(_clname, "IModelPlugin v0.1"))
        return static_cast< IModelPlugin*>(const_cast< TaskSketchModel*>(this));
    if (!strcmp(_clname, "ITaskSketchModel v0.1"))
        return static_cast< ITaskSketchModel*>(const_cast< TaskSketchModel*>(this));
    return QObject::qt_metacast(_clname);
}

int TaskSketchModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void TaskSketchModel::OnClose(PluginInfo * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TaskSketchModel::OnClose()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0x84, 0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    'p',  0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'M',  'o',  'd', 
    'u',  'l',  'e',  '.',  'T',  'e',  's',  't', 
    0x1b, 0x08, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0f, 0x00, 'T',  'a',  's',  'k',  'S',  'k', 
    'e',  't',  'c',  'h',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, 0x1a, 0x00, 0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x15, 0x10, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0xf0, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0xe0, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'T',  'y',  'p',  'e',  0x00, 0x00,
    0x0b, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    'M',  'o',  'd',  'e',  'l',  0x00, 0x00, 0x00,
    0x1b, 0x07, 0x00, 0x00, 0x09, 0x00, 'I',  'n', 
    't',  'e',  'r',  'f',  'a',  'c',  'e',  0x00,
    0x10, 0x00, 'I',  'T',  'a',  's',  'k',  'S', 
    'k',  'e',  't',  'c',  'h',  'M',  'o',  'd', 
    'e',  'l',  0x00, 0x00, 0x1b, 0x0b, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x0f, 0x00, 'T',  'a',  's',  'k',  'S',  'k', 
    'e',  't',  'c',  'h',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, 0x94, 0x11, 0x00, 0x00,
    0x17, 0x00, 'R',  'e',  'l',  'a',  't',  'e', 
    'd',  'P',  'l',  'u',  'g',  'i',  'n',  'I', 
    'n',  't',  'e',  'r',  'f',  'a',  'c',  'e', 
    's',  0x00, 0x00, 0x00, 'T',  0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 'H',  0x00, 0x00, 0x00,
    0x1a, 0x00, 'I',  'E',  'x',  't',  'e',  'n', 
    'd',  'a',  'b',  'l',  'e',  'D',  'a',  't', 
    'a',  'B',  'a',  's',  'e',  'M',  'a',  'n', 
    'a',  'g',  'e',  'r',  0x0e, 0x00, 'I',  'T', 
    'a',  's',  'k',  'T',  'r',  'e',  'e',  'M', 
    'o',  'd',  'e',  'l',  0x0e, 0x00, 'I',  'M', 
    'a',  'i',  'n',  'M',  'e',  'n',  'u',  'M', 
    'o',  'd',  'e',  'l',  0x8b, 0x01, 0x00, 0x00,
    0x0b, 0x05, 0x00, 0x00, 0x0b, 0x07, 0x00, 0x00,
    '(',  0x00, 0x00, 0x00, 'L',  0x00, 0x00, 0x00,
    'l',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 'p',  0x00, 0x00, 0x00,
    '0',  0x00, 0x00, 0x00, 'd',  0x00, 0x00, 0x00,
    'T',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0x84, 0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    'p',  0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'M',  'o',  'd', 
    'u',  'l',  'e',  '.',  'T',  'e',  's',  't', 
    0x15, 0x08, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0xf0, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0xe0, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'T',  'y',  'p',  'e',  0x00, 0x00,
    0x0b, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    'M',  'o',  'd',  'e',  'l',  0x00, 0x00, 0x00,
    0x1b, 0x07, 0x00, 0x00, 0x09, 0x00, 'I',  'n', 
    't',  'e',  'r',  'f',  'a',  'c',  'e',  0x00,
    0x10, 0x00, 'I',  'T',  'a',  's',  'k',  'S', 
    'k',  'e',  't',  'c',  'h',  'M',  'o',  'd', 
    'e',  'l',  0x00, 0x00, 0x1b, 0x0b, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x0f, 0x00, 'T',  'a',  's',  'k',  'S',  'k', 
    'e',  't',  'c',  'h',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, 0x94, 0x11, 0x00, 0x00,
    0x17, 0x00, 'R',  'e',  'l',  'a',  't',  'e', 
    'd',  'P',  'l',  'u',  'g',  'i',  'n',  'I', 
    'n',  't',  'e',  'r',  'f',  'a',  'c',  'e', 
    's',  0x00, 0x00, 0x00, 'T',  0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 'H',  0x00, 0x00, 0x00,
    0x1a, 0x00, 'I',  'E',  'x',  't',  'e',  'n', 
    'd',  'a',  'b',  'l',  'e',  'D',  'a',  't', 
    'a',  'B',  'a',  's',  'e',  'M',  'a',  'n', 
    'a',  'g',  'e',  'r',  0x0e, 0x00, 'I',  'T', 
    'a',  's',  'k',  'T',  'r',  'e',  'e',  'M', 
    'o',  'd',  'e',  'l',  0x0e, 0x00, 'I',  'M', 
    'a',  'i',  'n',  'M',  'e',  'n',  'u',  'M', 
    'o',  'd',  'e',  'l',  0x8b, 0x01, 0x00, 0x00,
    0x0b, 0x05, 0x00, 0x00, 0x0b, 0x07, 0x00, 0x00,
    '(',  0x00, 0x00, 0x00, 'L',  0x00, 0x00, 0x00,
    'l',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x1b, '(',  0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0f, 0x00, 'T',  'a',  's',  'k',  'S',  'k', 
    'e',  't',  'c',  'h',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, '1',  0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x1a, 0x00, 0xa1, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '0',  0x00, 0x00, 0x00,
    '0',  0x01, 0x00, 0x00, 'T',  0x01, 0x00, 0x00,
    '`',  0x01, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(TaskSketchModel, TaskSketchModel)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
