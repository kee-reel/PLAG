/****************************************************************************
** Meta object code from reading C++ file 'mainmenupluginview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainmenupluginview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainmenupluginview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainMenuPluginView_t {
    QByteArrayData data[11];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainMenuPluginView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainMenuPluginView_t qt_meta_stringdata_MainMenuPluginView = {
    {
QT_MOC_LITERAL(0, 0, 18), // "MainMenuPluginView"
QT_MOC_LITERAL(1, 19, 7), // "OnClose"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "IViewPlugin*"
QT_MOC_LITERAL(4, 41, 7), // "pointer"
QT_MOC_LITERAL(5, 49, 15), // "OpenChildPlugin"
QT_MOC_LITERAL(6, 65, 31), // "IMainMenuPluginModel::MenuItem*"
QT_MOC_LITERAL(7, 97, 8), // "menuItem"
QT_MOC_LITERAL(8, 106, 9), // "MetaInfo*"
QT_MOC_LITERAL(9, 116, 8), // "viewMeta"
QT_MOC_LITERAL(10, 125, 13) // "CloseMainMenu"

    },
    "MainMenuPluginView\0OnClose\0\0IViewPlugin*\0"
    "pointer\0OpenChildPlugin\0"
    "IMainMenuPluginModel::MenuItem*\0"
    "menuItem\0MetaInfo*\0viewMeta\0CloseMainMenu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainMenuPluginView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       1,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   38,    2, 0x08 /* Private */,
      10,    0,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    7,    9,
    QMetaType::Void,

       0        // eod
};

void MainMenuPluginView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainMenuPluginView *_t = static_cast<MainMenuPluginView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnClose((*reinterpret_cast< IViewPlugin*(*)>(_a[1]))); break;
        case 1: _t->OnClose(); break;
        case 2: _t->OpenChildPlugin((*reinterpret_cast< IMainMenuPluginModel::MenuItem*(*)>(_a[1])),(*reinterpret_cast< MetaInfo*(*)>(_a[2]))); break;
        case 3: _t->CloseMainMenu(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainMenuPluginView::*_t)(IViewPlugin * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainMenuPluginView::OnClose)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainMenuPluginView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainMenuPluginView::OnClose)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainMenuPluginView::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MainMenuPluginView.data,
      qt_meta_data_MainMenuPluginView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainMenuPluginView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainMenuPluginView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainMenuPluginView.stringdata0))
        return static_cast<void*>(const_cast< MainMenuPluginView*>(this));
    if (!strcmp(_clname, "IViewPlugin"))
        return static_cast< IViewPlugin*>(const_cast< MainMenuPluginView*>(this));
    if (!strcmp(_clname, "IViewPlugin v0.1"))
        return static_cast< IViewPlugin*>(const_cast< MainMenuPluginView*>(this));
    return QObject::qt_metacast(_clname);
}

int MainMenuPluginView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MainMenuPluginView::OnClose(IViewPlugin * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainMenuPluginView::OnClose()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
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
    0x12, 0x00, 'M',  'a',  'i',  'n',  'M',  'e', 
    'n',  'u',  'P',  'l',  'u',  'g',  'i',  'n', 
    'V',  'i',  'e',  'w',  0x1a, 0x00, 0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x15, 0x10, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0x8c, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    '|',  0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x0c, 0x00, 'M',  'a',  'i',  'n',  'M',  'e', 
    'n',  'u',  'V',  'i',  'e',  'w',  0x00, 0x00,
    0x1b, 0x07, 0x00, 0x00, 0x0a, 0x00, 'P',  'l', 
    'u',  'g',  'i',  'n',  'T',  'y',  'p',  'e', 
    0x0a, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    'V',  'i',  'e',  'w',  0x9b, 0x0a, 0x00, 0x00,
    0x0a, 0x00, 'P',  'a',  'r',  'e',  'n',  't', 
    'N',  'a',  'm',  'e',  0x0d, 0x00, 'M',  'a', 
    'i',  'n',  'M',  'e',  'n',  'u',  'M',  'o', 
    'd',  'e',  'l',  0x00, 0x1b, 0x0f, 0x00, 0x00,
    0x0b, 0x00, 'D',  'a',  't',  'a',  'M',  'a', 
    'n',  'a',  'g',  'e',  'r',  0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 'd',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 'D',  0x00, 0x00, 0x00,
    '(',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    'p',  0x00, 0x00, 0x00, '0',  0x00, 0x00, 0x00,
    'd',  0x00, 0x00, 0x00, 'T',  0x00, 0x00, 0x00
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
    0x8c, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    '|',  0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x0c, 0x00, 'M',  'a',  'i',  'n',  'M',  'e', 
    'n',  'u',  'V',  'i',  'e',  'w',  0x00, 0x00,
    0x1b, 0x07, 0x00, 0x00, 0x0a, 0x00, 'P',  'l', 
    'u',  'g',  'i',  'n',  'T',  'y',  'p',  'e', 
    0x0a, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    'V',  'i',  'e',  'w',  0x9b, 0x0a, 0x00, 0x00,
    0x0a, 0x00, 'P',  'a',  'r',  'e',  'n',  't', 
    'N',  'a',  'm',  'e',  0x0d, 0x00, 'M',  'a', 
    'i',  'n',  'M',  'e',  'n',  'u',  'M',  'o', 
    'd',  'e',  'l',  0x00, 0x1b, 0x0f, 0x00, 0x00,
    0x0b, 0x00, 'D',  'a',  't',  'a',  'M',  'a', 
    'n',  'a',  'g',  'e',  'r',  0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 'd',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 'D',  0x00, 0x00, 0x00,
    '(',  0x00, 0x00, 0x00, 0x9b, 0x1b, 0x00, 0x00,
    0x09, 0x00, 'c',  'l',  'a',  's',  's',  'N', 
    'a',  'm',  'e',  0x00, 0x12, 0x00, 'M',  'a', 
    'i',  'n',  'M',  'e',  'n',  'u',  'P',  'l', 
    'u',  'g',  'i',  'n',  'V',  'i',  'e',  'w', 
    '1',  0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x1a, 0x00, 0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    '0',  0x00, 0x00, 0x00, 0xcc, 0x00, 0x00, 0x00,
    0xf0, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(MainMenuPluginView, MainMenuPluginView)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
