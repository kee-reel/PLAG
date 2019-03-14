#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PluginLinker
TEMPLATE = lib
QT += core widgets


SOURCES += \
    pluginlinker.cpp \
    linkeritem.cpp

HEADERS += \
    pluginlinker.h \
    linkeritem.h \
    ../../PluginsInterfaces/ipluginlinker.h \
    ../../../Application/icoreplugin.h

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
