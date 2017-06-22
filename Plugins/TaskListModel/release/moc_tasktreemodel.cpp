/****************************************************************************
** Meta object code from reading C++ file 'tasktreemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tasktreemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tasktreemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TaskTreeModel_t {
    QByteArrayData data[4];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaskTreeModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaskTreeModel_t qt_meta_stringdata_TaskTreeModel = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TaskTreeModel"
QT_MOC_LITERAL(1, 14, 12), // "OpenTaskEdit"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 2) // "id"

    },
    "TaskTreeModel\0OpenTaskEdit\0\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskTreeModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void TaskTreeModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TaskTreeModel *_t = static_cast<TaskTreeModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OpenTaskEdit((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TaskTreeModel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TaskTreeModel::OpenTaskEdit)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TaskTreeModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TaskTreeModel.data,
      qt_meta_data_TaskTreeModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TaskTreeModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskTreeModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TaskTreeModel.stringdata0))
        return static_cast<void*>(const_cast< TaskTreeModel*>(this));
    if (!strcmp(_clname, "ITaskTreeModel"))
        return static_cast< ITaskTreeModel*>(const_cast< TaskTreeModel*>(this));
    if (!strcmp(_clname, "IModelPlugin v0.1"))
        return static_cast< IModelPlugin*>(const_cast< TaskTreeModel*>(this));
    if (!strcmp(_clname, "ITaskTreeModel v0.1"))
        return static_cast< ITaskTreeModel*>(const_cast< TaskTreeModel*>(this));
    return QObject::qt_metacast(_clname);
}

int TaskTreeModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TaskTreeModel::OpenTaskEdit(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    ',',  0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x18, 0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'M',  'o',  'd', 
    'u',  'l',  'e',  '.',  'T',  'e',  's',  't', 
    0x1b, 0x08, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0d, 0x00, 'T',  'a',  's',  'k',  'T',  'r', 
    'e',  'e',  'M',  'o',  'd',  'e',  'l',  0x00,
    'Z',  0xc0, 0xa0, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x95, 0x0f, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, 0x9c, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00,
    0x1b, 0x03, 0x00, 0x00, 0x04, 0x00, 'N',  'a', 
    'm',  'e',  0x00, 0x00, 0x0d, 0x00, 'T',  'a', 
    's',  'k',  'L',  'i',  's',  't',  'M',  'o', 
    'd',  'e',  'l',  0x00, 0x1b, 0x07, 0x00, 0x00,
    0x0a, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    'T',  'y',  'p',  'e',  0x0b, 0x00, 'P',  'l', 
    'u',  'g',  'i',  'n',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, 0x1b, 0x0b, 0x00, 0x00,
    0x0a, 0x00, 'P',  'a',  'r',  'e',  'n',  't', 
    'N',  'a',  'm',  'e',  0x00, 0x00, 0x00, 0x00,
    0x1b, 0x0e, 0x00, 0x00, 0x0b, 0x00, 'D',  'a', 
    't',  'a',  'M',  'a',  'n',  'a',  'g',  'e', 
    'r',  0x00, 0x00, 0x00, 0x19, 0x00, 'E',  'x', 
    't',  'e',  'n',  'd',  'a',  'b',  'l',  'e', 
    'D',  'a',  't',  'a',  'B',  'a',  's',  'e', 
    'M',  'a',  'n',  'a',  'g',  'e',  'r',  0x00,
    '\\', 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    'H',  0x00, 0x00, 0x00, '(',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 'l',  0x00, 0x00, 0x00,
    '0',  0x00, 0x00, 0x00, '`',  0x00, 0x00, 0x00,
    'P',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    ',',  0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x18, 0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'M',  'o',  'd', 
    'u',  'l',  'e',  '.',  'T',  'e',  's',  't', 
    0x15, 0x08, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0x9c, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x8c, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x0d, 0x00, 'T',  'a',  's',  'k',  'L',  'i', 
    's',  't',  'M',  'o',  'd',  'e',  'l',  0x00,
    0x1b, 0x07, 0x00, 0x00, 0x0a, 0x00, 'P',  'l', 
    'u',  'g',  'i',  'n',  'T',  'y',  'p',  'e', 
    0x0b, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    'M',  'o',  'd',  'e',  'l',  0x00, 0x00, 0x00,
    0x1b, 0x0b, 0x00, 0x00, 0x0a, 0x00, 'P',  'a', 
    'r',  'e',  'n',  't',  'N',  'a',  'm',  'e', 
    0x00, 0x00, 0x00, 0x00, 0x1b, 0x0e, 0x00, 0x00,
    0x0b, 0x00, 'D',  'a',  't',  'a',  'M',  'a', 
    'n',  'a',  'g',  'e',  'r',  0x00, 0x00, 0x00,
    0x19, 0x00, 'E',  'x',  't',  'e',  'n',  'd', 
    'a',  'b',  'l',  'e',  'D',  'a',  't',  'a', 
    'B',  'a',  's',  'e',  'M',  'a',  'n',  'a', 
    'g',  'e',  'r',  0x00, '\\', 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 'H',  0x00, 0x00, 0x00,
    '(',  0x00, 0x00, 0x00, 0x9b, 0x1d, 0x00, 0x00,
    0x09, 0x00, 'c',  'l',  'a',  's',  's',  'N', 
    'a',  'm',  'e',  0x00, 0x0d, 0x00, 'T',  'a', 
    's',  'k',  'T',  'r',  'e',  'e',  'M',  'o', 
    'd',  'e',  'l',  0x00, '1',  0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    'Z',  0xc0, 0xa0, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '0',  0x00, 0x00, 0x00,
    0xdc, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00,
    0x08, 0x01, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(TaskTreeModel, TaskTreeModel)

QT_END_MOC_NAMESPACE
