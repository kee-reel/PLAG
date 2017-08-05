/****************************************************************************
** Meta object code from reading C++ file 'cipherdatabasesourceplugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cipherdatabasesourceplugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cipherdatabasesourceplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CipherDataBaseSourcePlugin_t {
    QByteArrayData data[7];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CipherDataBaseSourcePlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CipherDataBaseSourcePlugin_t qt_meta_stringdata_CipherDataBaseSourcePlugin = {
    {
QT_MOC_LITERAL(0, 0, 26), // "CipherDataBaseSourcePlugin"
QT_MOC_LITERAL(1, 27, 7), // "OnClose"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "PluginInfo*"
QT_MOC_LITERAL(4, 48, 7), // "pointer"
QT_MOC_LITERAL(5, 56, 21), // "ReferencePluginClosed"
QT_MOC_LITERAL(6, 78, 10) // "pluginInfo"

    },
    "CipherDataBaseSourcePlugin\0OnClose\0\0"
    "PluginInfo*\0pointer\0ReferencePluginClosed\0"
    "pluginInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CipherDataBaseSourcePlugin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       1,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    6,

       0        // eod
};

void CipherDataBaseSourcePlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CipherDataBaseSourcePlugin *_t = static_cast<CipherDataBaseSourcePlugin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnClose((*reinterpret_cast< PluginInfo*(*)>(_a[1]))); break;
        case 1: _t->OnClose(); break;
        case 2: _t->ReferencePluginClosed((*reinterpret_cast< PluginInfo*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CipherDataBaseSourcePlugin::*_t)(PluginInfo * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CipherDataBaseSourcePlugin::OnClose)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CipherDataBaseSourcePlugin::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CipherDataBaseSourcePlugin::OnClose)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CipherDataBaseSourcePlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CipherDataBaseSourcePlugin.data,
      qt_meta_data_CipherDataBaseSourcePlugin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CipherDataBaseSourcePlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CipherDataBaseSourcePlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CipherDataBaseSourcePlugin.stringdata0))
        return static_cast<void*>(const_cast< CipherDataBaseSourcePlugin*>(this));
    if (!strcmp(_clname, "IDataBaseSourcePlugin"))
        return static_cast< IDataBaseSourcePlugin*>(const_cast< CipherDataBaseSourcePlugin*>(this));
    if (!strcmp(_clname, "IDataSourcePlugin v0.1"))
        return static_cast< IDataSourcePlugin*>(const_cast< CipherDataBaseSourcePlugin*>(this));
    if (!strcmp(_clname, "IDataBaseSourcePlugin v0.1"))
        return static_cast< IDataBaseSourcePlugin*>(const_cast< CipherDataBaseSourcePlugin*>(this));
    return QObject::qt_metacast(_clname);
}

int CipherDataBaseSourcePlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void CipherDataBaseSourcePlugin::OnClose(PluginInfo * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CipherDataBaseSourcePlugin::OnClose()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    'T',  0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    '@',  0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x18, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'D',  'B',  'M', 
    'o',  'd',  'u',  'l',  'e',  '.',  'T',  'e', 
    's',  't',  0x00, 0x00, 0x9b, 0x08, 0x00, 0x00,
    0x09, 0x00, 'c',  'l',  'a',  's',  's',  'N', 
    'a',  'm',  'e',  0x00, 0x1a, 0x00, 'C',  'i', 
    'p',  'h',  'e',  'r',  'D',  'a',  't',  'a', 
    'B',  'a',  's',  'e',  'S',  'o',  'u',  'r', 
    'c',  'e',  'P',  'l',  'u',  'g',  'i',  'n', 
    0x1a, 0x00, 0xa1, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x95, 0x11, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, 0xb4, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00,
    0x1b, 0x03, 0x00, 0x00, 0x04, 0x00, 'T',  'y', 
    'p',  'e',  0x00, 0x00, 0x0a, 0x00, 'D',  'a', 
    't',  'a',  'S',  'o',  'u',  'r',  'c',  'e', 
    0x9b, 0x06, 0x00, 0x00, 0x09, 0x00, 'I',  'n', 
    't',  'e',  'r',  'f',  'a',  'c',  'e',  0x00,
    0x15, 0x00, 'I',  'D',  'a',  't',  'a',  'B', 
    'a',  's',  'e',  'S',  'o',  'u',  'r',  'c', 
    'e',  'P',  'l',  'u',  'g',  'i',  'n',  0x00,
    0x1b, 0x0b, 0x00, 0x00, 0x04, 0x00, 'N',  'a', 
    'm',  'e',  0x00, 0x00, 0x14, 0x00, 'C',  'i', 
    'p',  'h',  'e',  'r',  'D',  'a',  't',  'a', 
    'b',  'a',  's',  'e',  'S',  'o',  'u',  'r', 
    'c',  'e',  0x00, 0x00, 0x14, 0x12, 0x00, 0x00,
    0x17, 0x00, 'R',  'e',  'l',  'a',  't',  'e', 
    'd',  'P',  'l',  'u',  'g',  'i',  'n',  'I', 
    'n',  't',  'e',  'r',  'f',  'a',  'c',  'e', 
    's',  0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x8b, 0x01, 0x00, 0x00,
    '$',  0x00, 0x00, 0x00, 'L',  0x00, 0x00, 0x00,
    'p',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '|',  0x00, 0x00, 0x00,
    '4',  0x00, 0x00, 0x00, 'p',  0x00, 0x00, 0x00,
    '`',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    'T',  0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    '@',  0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x18, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'D',  'B',  'M', 
    'o',  'd',  'u',  'l',  'e',  '.',  'T',  'e', 
    's',  't',  0x00, 0x00, 0x95, 0x08, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, 0xb4, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00,
    0x1b, 0x03, 0x00, 0x00, 0x04, 0x00, 'T',  'y', 
    'p',  'e',  0x00, 0x00, 0x0a, 0x00, 'D',  'a', 
    't',  'a',  'S',  'o',  'u',  'r',  'c',  'e', 
    0x9b, 0x06, 0x00, 0x00, 0x09, 0x00, 'I',  'n', 
    't',  'e',  'r',  'f',  'a',  'c',  'e',  0x00,
    0x15, 0x00, 'I',  'D',  'a',  't',  'a',  'B', 
    'a',  's',  'e',  'S',  'o',  'u',  'r',  'c', 
    'e',  'P',  'l',  'u',  'g',  'i',  'n',  0x00,
    0x1b, 0x0b, 0x00, 0x00, 0x04, 0x00, 'N',  'a', 
    'm',  'e',  0x00, 0x00, 0x14, 0x00, 'C',  'i', 
    'p',  'h',  'e',  'r',  'D',  'a',  't',  'a', 
    'b',  'a',  's',  'e',  'S',  'o',  'u',  'r', 
    'c',  'e',  0x00, 0x00, 0x14, 0x12, 0x00, 0x00,
    0x17, 0x00, 'R',  'e',  'l',  'a',  't',  'e', 
    'd',  'P',  'l',  'u',  'g',  'i',  'n',  'I', 
    'n',  't',  'e',  'r',  'f',  'a',  'c',  'e', 
    's',  0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x8b, 0x01, 0x00, 0x00,
    '$',  0x00, 0x00, 0x00, 'L',  0x00, 0x00, 0x00,
    'p',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x1b, '!',  0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x1a, 0x00, 'C',  'i',  'p',  'h',  'e',  'r', 
    'D',  'a',  't',  'a',  'B',  'a',  's',  'e', 
    'S',  'o',  'u',  'r',  'c',  'e',  'P',  'l', 
    'u',  'g',  'i',  'n',  '1',  0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x1a, 0x00, 0xa1, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '4',  0x00, 0x00, 0x00,
    0xf8, 0x00, 0x00, 0x00, '$',  0x01, 0x00, 0x00,
    '0',  0x01, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(CipherDataBaseSourcePlugin, CipherDataBaseSourcePlugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
