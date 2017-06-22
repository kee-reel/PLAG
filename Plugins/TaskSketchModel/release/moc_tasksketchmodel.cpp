/****************************************************************************
** Meta object code from reading C++ file 'tasksketchmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
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
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TaskSketchModel_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaskSketchModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaskSketchModel_t qt_meta_stringdata_TaskSketchModel = {
    {
QT_MOC_LITERAL(0, 0, 15) // "TaskSketchModel"

    },
    "TaskSketchModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskSketchModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void TaskSketchModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
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
    return _id;
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    '@',  0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    ',',  0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'M',  'o',  'd', 
    'u',  'l',  'e',  '.',  'T',  'e',  's',  't', 
    0x1b, 0x08, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0f, 0x00, 'T',  'a',  's',  'k',  'S',  'k', 
    'e',  't',  'c',  'h',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, 'Z',  0xc0, 0xa0, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x15, 0x10, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0xac, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x9c, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x0f, 0x00, 'T',  'a',  's',  'k',  'S',  'k', 
    'e',  't',  'c',  'h',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, 0x9b, 0x07, 0x00, 0x00,
    0x0a, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    'T',  'y',  'p',  'e',  0x0b, 0x00, 'P',  'l', 
    'u',  'g',  'i',  'n',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, 0x9b, 0x0b, 0x00, 0x00,
    0x0a, 0x00, 'P',  'a',  'r',  'e',  'n',  't', 
    'N',  'a',  'm',  'e',  0x0d, 0x00, 'T',  'a', 
    's',  'k',  'L',  'i',  's',  't',  'M',  'o', 
    'd',  'e',  'l',  0x00, 0x1b, 0x10, 0x00, 0x00,
    0x0b, 0x00, 'D',  'a',  't',  'a',  'M',  'a', 
    'n',  'a',  'g',  'e',  'r',  0x00, 0x00, 0x00,
    0x19, 0x00, 'E',  'x',  't',  'e',  'n',  'd', 
    'a',  'b',  'l',  'e',  'D',  'a',  't',  'a', 
    'B',  'a',  's',  'e',  'M',  'a',  'n',  'a', 
    'g',  'e',  'r',  0x00, 'l',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 'L',  0x00, 0x00, 0x00,
    ',',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    'p',  0x00, 0x00, 0x00, '0',  0x00, 0x00, 0x00,
    'd',  0x00, 0x00, 0x00, 'T',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    '@',  0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    ',',  0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'M',  'o',  'd', 
    'u',  'l',  'e',  '.',  'T',  'e',  's',  't', 
    0x15, 0x08, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0xac, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x9c, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x0f, 0x00, 'T',  'a',  's',  'k',  'S',  'k', 
    'e',  't',  'c',  'h',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, 0x9b, 0x07, 0x00, 0x00,
    0x0a, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    'T',  'y',  'p',  'e',  0x0b, 0x00, 'P',  'l', 
    'u',  'g',  'i',  'n',  'M',  'o',  'd',  'e', 
    'l',  0x00, 0x00, 0x00, 0x9b, 0x0b, 0x00, 0x00,
    0x0a, 0x00, 'P',  'a',  'r',  'e',  'n',  't', 
    'N',  'a',  'm',  'e',  0x0d, 0x00, 'T',  'a', 
    's',  'k',  'L',  'i',  's',  't',  'M',  'o', 
    'd',  'e',  'l',  0x00, 0x1b, 0x10, 0x00, 0x00,
    0x0b, 0x00, 'D',  'a',  't',  'a',  'M',  'a', 
    'n',  'a',  'g',  'e',  'r',  0x00, 0x00, 0x00,
    0x19, 0x00, 'E',  'x',  't',  'e',  'n',  'd', 
    'a',  'b',  'l',  'e',  'D',  'a',  't',  'a', 
    'B',  'a',  's',  'e',  'M',  'a',  'n',  'a', 
    'g',  'e',  'r',  0x00, 'l',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 'L',  0x00, 0x00, 0x00,
    ',',  0x00, 0x00, 0x00, 0x9b, 0x1f, 0x00, 0x00,
    0x09, 0x00, 'c',  'l',  'a',  's',  's',  'N', 
    'a',  'm',  'e',  0x00, 0x0f, 0x00, 'T',  'a', 
    's',  'k',  'S',  'k',  'e',  't',  'c',  'h', 
    'M',  'o',  'd',  'e',  'l',  0x00, 0x00, 0x00,
    '1',  0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 'Z',  0xc0, 0xa0, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    '0',  0x00, 0x00, 0x00, 0xec, 0x00, 0x00, 0x00,
    0x10, 0x01, 0x00, 0x00, 0x1c, 0x01, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(TaskSketchModel, TaskSketchModel)

QT_END_MOC_NAMESPACE
