/****************************************************************************
** Meta object code from reading C++ file 'emptypluginview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../emptypluginview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emptypluginview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EmptyPluginView_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EmptyPluginView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EmptyPluginView_t qt_meta_stringdata_EmptyPluginView = {
    {
QT_MOC_LITERAL(0, 0, 15) // "EmptyPluginView"

    },
    "EmptyPluginView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EmptyPluginView[] = {

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

void EmptyPluginView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject EmptyPluginView::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EmptyPluginView.data,
      qt_meta_data_EmptyPluginView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EmptyPluginView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EmptyPluginView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EmptyPluginView.stringdata0))
        return static_cast<void*>(const_cast< EmptyPluginView*>(this));
    if (!strcmp(_clname, "IPluginView"))
        return static_cast< IPluginView*>(const_cast< EmptyPluginView*>(this));
    if (!strcmp(_clname, "IPluginView v0.1"))
        return static_cast< IPluginView*>(const_cast< EmptyPluginView*>(this));
    return QObject::qt_metacast(_clname);
}

int EmptyPluginView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    0x04, 0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xf0, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'M',  'o',  'd', 
    'u',  'l',  'e',  '.',  'T',  'e',  's',  't', 
    0x1b, 0x08, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0f, 0x00, 'E',  'm',  'p',  't',  'y',  'P', 
    'l',  'u',  'g',  'i',  'n',  'V',  'i',  'e', 
    'w',  0x00, 0x00, 0x00, 0x1a, 0x00, 0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x15, 0x10, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    'p',  0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
    'd',  0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x09, 0x00, 'E',  'm',  'p',  't',  'y',  'V', 
    'i',  'e',  'w',  0x00, 0x9b, 0x06, 0x00, 0x00,
    0x0a, 0x00, 'M',  'o',  'd',  'u',  'l',  'e', 
    'T',  'y',  'p',  'e',  0x08, 0x00, 'T',  'o', 
    'o',  'l',  'V',  'i',  'e',  'w',  0x00, 0x00,
    0x1b, 0x0b, 0x00, 0x00, 0x10, 0x00, 'P',  'a', 
    'r',  'e',  'n',  't',  'M',  'o',  'd',  'u', 
    'l',  'e',  'N',  'a',  'm',  'e',  0x00, 0x00,
    0x0a, 0x00, 'E',  'm',  'p',  't',  'y',  'M', 
    'o',  'd',  'e',  'l',  '$',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '@',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 'p',  0x00, 0x00, 0x00,
    '0',  0x00, 0x00, 0x00, 'd',  0x00, 0x00, 0x00,
    'T',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0x04, 0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xf0, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'T',  'i',  'm',  'e',  'K',  'e', 
    'e',  'p',  'e',  'r',  '.',  'M',  'o',  'd', 
    'u',  'l',  'e',  '.',  'T',  'e',  's',  't', 
    0x15, 0x08, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    'p',  0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
    'd',  0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x09, 0x00, 'E',  'm',  'p',  't',  'y',  'V', 
    'i',  'e',  'w',  0x00, 0x9b, 0x06, 0x00, 0x00,
    0x0a, 0x00, 'M',  'o',  'd',  'u',  'l',  'e', 
    'T',  'y',  'p',  'e',  0x08, 0x00, 'T',  'o', 
    'o',  'l',  'V',  'i',  'e',  'w',  0x00, 0x00,
    0x1b, 0x0b, 0x00, 0x00, 0x10, 0x00, 'P',  'a', 
    'r',  'e',  'n',  't',  'M',  'o',  'd',  'u', 
    'l',  'e',  'N',  'a',  'm',  'e',  0x00, 0x00,
    0x0a, 0x00, 'E',  'm',  'p',  't',  'y',  'M', 
    'o',  'd',  'e',  'l',  '$',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '@',  0x00, 0x00, 0x00,
    0x1b, 0x18, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0f, 0x00, 'E',  'm',  'p',  't',  'y',  'P', 
    'l',  'u',  'g',  'i',  'n',  'V',  'i',  'e', 
    'w',  0x00, 0x00, 0x00, '1',  0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x1a, 0x00, 0xa1, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '0',  0x00, 0x00, 0x00,
    0xb0, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00,
    0xe0, 0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(EmptyPluginView, EmptyPluginView)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
