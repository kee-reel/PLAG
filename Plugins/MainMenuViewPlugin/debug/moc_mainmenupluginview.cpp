/****************************************************************************
** Meta object code from reading C++ file 'mainmenupluginview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
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
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainMenuPluginView_t {
    QByteArrayData data[29];
    char stringdata[361];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainMenuPluginView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainMenuPluginView_t qt_meta_stringdata_MainMenuPluginView = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 7),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 11),
QT_MOC_LITERAL(4, 40, 7),
QT_MOC_LITERAL(5, 48, 14),
QT_MOC_LITERAL(6, 63, 25),
QT_MOC_LITERAL(7, 89, 4),
QT_MOC_LITERAL(8, 94, 9),
QT_MOC_LITERAL(9, 104, 8),
QT_MOC_LITERAL(10, 113, 21),
QT_MOC_LITERAL(11, 135, 10),
QT_MOC_LITERAL(12, 146, 4),
QT_MOC_LITERAL(13, 151, 13),
QT_MOC_LITERAL(14, 165, 5),
QT_MOC_LITERAL(15, 171, 8),
QT_MOC_LITERAL(16, 180, 6),
QT_MOC_LITERAL(17, 187, 5),
QT_MOC_LITERAL(18, 193, 15),
QT_MOC_LITERAL(19, 209, 12),
QT_MOC_LITERAL(20, 222, 11),
QT_MOC_LITERAL(21, 234, 23),
QT_MOC_LITERAL(22, 258, 14),
QT_MOC_LITERAL(23, 273, 20),
QT_MOC_LITERAL(24, 294, 12),
QT_MOC_LITERAL(25, 307, 15),
QT_MOC_LITERAL(26, 323, 8),
QT_MOC_LITERAL(27, 332, 13),
QT_MOC_LITERAL(28, 346, 13)
    },
    "MainMenuPluginView\0OnClose\0\0PluginInfo*\0"
    "pointer\0OnItemSelected\0IMainMenuModel::MenuItem*\0"
    "meta\0MetaInfo*\0viewMeta\0ReferencePluginClosed\0"
    "pluginInfo\0Open\0IModelPlugin*\0model\0"
    "QWidget*\0parent\0Close\0SetRootMenuItem\0"
    "RootMenuItem\0AddSubitems\0"
    "MenuItemGraphicsObject*\0ParentMenuItem\0"
    "ParentMenuItemStruct\0WipeAllItems\0"
    "OpenChildPlugin\0menuItem\0CloseMainMenu\0"
    "ZoomAnimation\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainMenuPluginView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06,
       1,    0,   82,    2, 0x06,
       5,    2,   83,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      10,    1,   88,    2, 0x0a,
      12,    2,   91,    2, 0x0a,
      17,    0,   96,    2, 0x0a,
      18,    1,   97,    2, 0x0a,
      20,    2,  100,    2, 0x0a,
      24,    0,  105,    2, 0x0a,
      25,    2,  106,    2, 0x08,
      27,    0,  111,    2, 0x08,
       5,    1,  112,    2, 0x08,
      28,    0,  115,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    7,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,   11,
    QMetaType::Bool, 0x80000000 | 13, 0x80000000 | 15,   14,   16,
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 6,   19,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 6,   22,   23,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,   26,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   26,
    QMetaType::Void,

       0        // eod
};

void MainMenuPluginView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainMenuPluginView *_t = static_cast<MainMenuPluginView *>(_o);
        switch (_id) {
        case 0: _t->OnClose((*reinterpret_cast< PluginInfo*(*)>(_a[1]))); break;
        case 1: _t->OnClose(); break;
        case 2: _t->OnItemSelected((*reinterpret_cast< IMainMenuModel::MenuItem*(*)>(_a[1])),(*reinterpret_cast< MetaInfo*(*)>(_a[2]))); break;
        case 3: _t->ReferencePluginClosed((*reinterpret_cast< PluginInfo*(*)>(_a[1]))); break;
        case 4: { bool _r = _t->Open((*reinterpret_cast< IModelPlugin*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->Close();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: _t->SetRootMenuItem((*reinterpret_cast< IMainMenuModel::MenuItem*(*)>(_a[1]))); break;
        case 7: _t->AddSubitems((*reinterpret_cast< MenuItemGraphicsObject*(*)>(_a[1])),(*reinterpret_cast< IMainMenuModel::MenuItem*(*)>(_a[2]))); break;
        case 8: _t->WipeAllItems(); break;
        case 9: _t->OpenChildPlugin((*reinterpret_cast< IMainMenuModel::MenuItem*(*)>(_a[1])),(*reinterpret_cast< MetaInfo*(*)>(_a[2]))); break;
        case 10: _t->CloseMainMenu(); break;
        case 11: _t->OnItemSelected((*reinterpret_cast< MenuItemGraphicsObject*(*)>(_a[1]))); break;
        case 12: _t->ZoomAnimation(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MenuItemGraphicsObject* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MenuItemGraphicsObject* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainMenuPluginView::*_t)(PluginInfo * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainMenuPluginView::OnClose)) {
                *result = 0;
            }
        }
        {
            typedef void (MainMenuPluginView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainMenuPluginView::OnClose)) {
                *result = 1;
            }
        }
        {
            typedef void (MainMenuPluginView::*_t)(IMainMenuModel::MenuItem * , MetaInfo * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainMenuPluginView::OnItemSelected)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject MainMenuPluginView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainMenuPluginView.data,
      qt_meta_data_MainMenuPluginView,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainMenuPluginView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainMenuPluginView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainMenuPluginView.stringdata))
        return static_cast<void*>(const_cast< MainMenuPluginView*>(this));
    if (!strcmp(_clname, "IViewPlugin"))
        return static_cast< IViewPlugin*>(const_cast< MainMenuPluginView*>(this));
    if (!strcmp(_clname, "IViewPlugin v0.1"))
        return static_cast< IViewPlugin*>(const_cast< MainMenuPluginView*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainMenuPluginView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainMenuPluginView::OnClose(PluginInfo * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainMenuPluginView::OnClose()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainMenuPluginView::OnItemSelected(IMainMenuModel::MenuItem * _t1, MetaInfo * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    0x71, 0x62, 0x6a, 0x73, 0x01, 0x00, 0x00, 0x00,
    0x38, 0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x24, 0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 0x49, 0x49, 0x44, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x54, 0x69, 0x6d, 0x65, 0x4b, 0x65,
    0x65, 0x70, 0x65, 0x72, 0x2e, 0x4d, 0x6f, 0x64,
    0x75, 0x6c, 0x65, 0x2e, 0x54, 0x65, 0x73, 0x74,
    0x1b, 0x08, 0x00, 0x00, 0x09, 0x00, 0x63, 0x6c,
    0x61, 0x73, 0x73, 0x4e, 0x61, 0x6d, 0x65, 0x00,
    0x12, 0x00, 0x4d, 0x61, 0x69, 0x6e, 0x4d, 0x65,
    0x6e, 0x75, 0x50, 0x6c, 0x75, 0x67, 0x69, 0x6e,
    0x56, 0x69, 0x65, 0x77, 0x3a, 0x40, 0xa0, 0x00,
    0x07, 0x00, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f,
    0x6e, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x05, 0x00, 0x64, 0x65, 0x62, 0x75, 0x67, 0x00,
    0x15, 0x10, 0x00, 0x00, 0x08, 0x00, 0x4d, 0x65,
    0x74, 0x61, 0x44, 0x61, 0x74, 0x61, 0x00, 0x00,
    0xa4, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x94, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 0x54, 0x79, 0x70, 0x65, 0x00, 0x00,
    0x0a, 0x00, 0x50, 0x6c, 0x75, 0x67, 0x69, 0x6e,
    0x56, 0x69, 0x65, 0x77, 0x9b, 0x06, 0x00, 0x00,
    0x09, 0x00, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x66,
    0x61, 0x63, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x9b, 0x08, 0x00, 0x00, 0x04, 0x00, 0x4e, 0x61,
    0x6d, 0x65, 0x00, 0x00, 0x0c, 0x00, 0x4d, 0x61,
    0x69, 0x6e, 0x4d, 0x65, 0x6e, 0x75, 0x56, 0x69,
    0x65, 0x77, 0x00, 0x00, 0x94, 0x0e, 0x00, 0x00,
    0x17, 0x00, 0x52, 0x65, 0x6c, 0x61, 0x74, 0x65,
    0x64, 0x50, 0x6c, 0x75, 0x67, 0x69, 0x6e, 0x49,
    0x6e, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65,
    0x73, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x0e, 0x00, 0x49, 0x4d, 0x61, 0x69, 0x6e, 0x4d,
    0x65, 0x6e, 0x75, 0x4d, 0x6f, 0x64, 0x65, 0x6c,
    0x8b, 0x01, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
    0x38, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x70, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x64, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    0x71, 0x62, 0x6a, 0x73, 0x01, 0x00, 0x00, 0x00,
    0x38, 0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x24, 0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 0x49, 0x49, 0x44, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x54, 0x69, 0x6d, 0x65, 0x4b, 0x65,
    0x65, 0x70, 0x65, 0x72, 0x2e, 0x4d, 0x6f, 0x64,
    0x75, 0x6c, 0x65, 0x2e, 0x54, 0x65, 0x73, 0x74,
    0x15, 0x08, 0x00, 0x00, 0x08, 0x00, 0x4d, 0x65,
    0x74, 0x61, 0x44, 0x61, 0x74, 0x61, 0x00, 0x00,
    0xa4, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x94, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 0x54, 0x79, 0x70, 0x65, 0x00, 0x00,
    0x0a, 0x00, 0x50, 0x6c, 0x75, 0x67, 0x69, 0x6e,
    0x56, 0x69, 0x65, 0x77, 0x9b, 0x06, 0x00, 0x00,
    0x09, 0x00, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x66,
    0x61, 0x63, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x9b, 0x08, 0x00, 0x00, 0x04, 0x00, 0x4e, 0x61,
    0x6d, 0x65, 0x00, 0x00, 0x0c, 0x00, 0x4d, 0x61,
    0x69, 0x6e, 0x4d, 0x65, 0x6e, 0x75, 0x56, 0x69,
    0x65, 0x77, 0x00, 0x00, 0x94, 0x0e, 0x00, 0x00,
    0x17, 0x00, 0x52, 0x65, 0x6c, 0x61, 0x74, 0x65,
    0x64, 0x50, 0x6c, 0x75, 0x67, 0x69, 0x6e, 0x49,
    0x6e, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65,
    0x73, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x0e, 0x00, 0x49, 0x4d, 0x61, 0x69, 0x6e, 0x4d,
    0x65, 0x6e, 0x75, 0x4d, 0x6f, 0x64, 0x65, 0x6c,
    0x8b, 0x01, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
    0x38, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x9b, 0x1e, 0x00, 0x00,
    0x09, 0x00, 0x63, 0x6c, 0x61, 0x73, 0x73, 0x4e,
    0x61, 0x6d, 0x65, 0x00, 0x12, 0x00, 0x4d, 0x61,
    0x69, 0x6e, 0x4d, 0x65, 0x6e, 0x75, 0x50, 0x6c,
    0x75, 0x67, 0x69, 0x6e, 0x56, 0x69, 0x65, 0x77,
    0x31, 0x00, 0x00, 0x00, 0x05, 0x00, 0x64, 0x65,
    0x62, 0x75, 0x67, 0x00, 0x3a, 0x40, 0xa0, 0x00,
    0x07, 0x00, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f,
    0x6e, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0xe4, 0x00, 0x00, 0x00,
    0x08, 0x01, 0x00, 0x00, 0x14, 0x01, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(MainMenuPluginView, MainMenuPluginView)

QT_END_MOC_NAMESPACE
