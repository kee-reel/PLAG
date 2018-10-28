
TARGET = NewArchTestPlugin
TEMPLATE = lib
QT += widgets

SOURCES += \
    newarchtestplugin.cpp

HEADERS +=\
    newarchtestplugin.h

DISTFILES += \
    PluginMeta.json

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)
