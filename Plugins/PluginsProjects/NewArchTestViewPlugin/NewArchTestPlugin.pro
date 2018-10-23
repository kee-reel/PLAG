
TARGET = NewArchTestPlugin
TEMPLATE = lib
QT += widgets

SOURCES += \
    newarchtestplugin.cpp

HEADERS +=\
    newarchtestplugin.h

DISTFILES += \
    PluginMeta.json

include(../../PluginsCommon/ViewBuildInfo.pri)
