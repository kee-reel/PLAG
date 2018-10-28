
TARGET = NewArchTestView
TEMPLATE = lib
QT += widgets

SOURCES += \
    newarchtestview.cpp

HEADERS += \
    newarchtestview.h

DEFINES += \
    PLUGIN_BASE_QWIDGET
    
DISTFILES += \
    PluginMeta.json

include(../../PluginsCommon/BuildInfo.pri)

FORMS += \
    form.ui
