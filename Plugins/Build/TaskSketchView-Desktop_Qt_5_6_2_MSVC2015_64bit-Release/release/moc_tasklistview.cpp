/****************************************************************************
** Meta object code from reading C++ file 'tasklistview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../TaskSketchView/tasklistview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tasklistview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TaskListView_t {
    QByteArrayData data[3];
    char stringdata0[20];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaskListView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaskListView_t qt_meta_stringdata_TaskListView = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TaskListView"
QT_MOC_LITERAL(1, 13, 5), // "Close"
QT_MOC_LITERAL(2, 19, 0) // ""

    },
    "TaskListView\0Close\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskListView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool,

       0        // eod
};

void TaskListView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TaskListView *_t = static_cast<TaskListView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->Close();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject TaskListView::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TaskListView.data,
      qt_meta_data_TaskListView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TaskListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskListView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TaskListView.stringdata0))
        return static_cast<void*>(const_cast< TaskListView*>(this));
    if (!strcmp(_clname, "IViewPlugin"))
        return static_cast< IViewPlugin*>(const_cast< TaskListView*>(this));
    if (!strcmp(_clname, "IViewPlugin v0.1"))
        return static_cast< IViewPlugin*>(const_cast< TaskListView*>(this));
    return QObject::qt_metacast(_clname);
}

int TaskListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    ' ',  0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x0c, 0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'M',  'o',  'd', 
    'u',  'l',  'e',  '.',  'T',  'e',  's',  't', 
    0x1b, 0x08, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0c, 0x00, 'T',  'a',  's',  'k',  'L',  'i', 
    's',  't',  'V',  'i',  'e',  'w',  0x00, 0x00,
    'Z',  0xc0, 0xa0, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x95, 0x0f, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, 0x90, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x1b, 0x03, 0x00, 0x00, 0x04, 0x00, 'N',  'a', 
    'm',  'e',  0x00, 0x00, 0x0e, 0x00, 'T',  'a', 
    's',  'k',  'S',  'k',  'e',  't',  'c',  'h', 
    'V',  'i',  'e',  'w',  0x1b, 0x07, 0x00, 0x00,
    0x0a, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    'T',  'y',  'p',  'e',  0x0a, 0x00, 'P',  'l', 
    'u',  'g',  'i',  'n',  'V',  'i',  'e',  'w', 
    0x9b, 0x0a, 0x00, 0x00, 0x0a, 0x00, 'P',  'a', 
    'r',  'e',  'n',  't',  'N',  'a',  'm',  'e', 
    0x0f, 0x00, 'T',  'a',  's',  'k',  'S',  'k', 
    'e',  't',  'c',  'h',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, 0x9b, 0x0f, 0x00, 0x00,
    0x0b, 0x00, 'D',  'a',  't',  'a',  'M',  'a', 
    'n',  'a',  'g',  'e',  'r',  0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 'h',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 'D',  0x00, 0x00, 0x00,
    '(',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    'l',  0x00, 0x00, 0x00, '0',  0x00, 0x00, 0x00,
    '`',  0x00, 0x00, 0x00, 'P',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    ' ',  0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x0c, 0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'M',  'o',  'd', 
    'u',  'l',  'e',  '.',  'T',  'e',  's',  't', 
    0x15, 0x08, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0x90, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x0e, 0x00, 'T',  'a',  's',  'k',  'S',  'k', 
    'e',  't',  'c',  'h',  'V',  'i',  'e',  'w', 
    0x1b, 0x07, 0x00, 0x00, 0x0a, 0x00, 'P',  'l', 
    'u',  'g',  'i',  'n',  'T',  'y',  'p',  'e', 
    0x0a, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    'V',  'i',  'e',  'w',  0x9b, 0x0a, 0x00, 0x00,
    0x0a, 0x00, 'P',  'a',  'r',  'e',  'n',  't', 
    'N',  'a',  'm',  'e',  0x0f, 0x00, 'T',  'a', 
    's',  'k',  'S',  'k',  'e',  't',  'c',  'h', 
    'M',  'o',  'd',  'e',  'l',  0x00, 0x00, 0x00,
    0x9b, 0x0f, 0x00, 0x00, 0x0b, 0x00, 'D',  'a', 
    't',  'a',  'M',  'a',  'n',  'a',  'g',  'e', 
    'r',  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    'h',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    'D',  0x00, 0x00, 0x00, '(',  0x00, 0x00, 0x00,
    0x1b, 0x1c, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0c, 0x00, 'T',  'a',  's',  'k',  'L',  'i', 
    's',  't',  'V',  'i',  'e',  'w',  0x00, 0x00,
    '1',  0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 'Z',  0xc0, 0xa0, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    '0',  0x00, 0x00, 0x00, 0xd0, 0x00, 0x00, 0x00,
    0xf0, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(TaskListView, TaskListView)

QT_END_MOC_NAMESPACE
