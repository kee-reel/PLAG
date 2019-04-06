#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = RootPluginLinker
TEMPLATE = lib
QT += core widgets


SOURCES += \
    linkeritem.cpp \
    pluginlinkercore.cpp

HEADERS += \
    linkeritem.h \
    ../../PluginsInterfaces/ipluginlinker.h \
    ../../../Application/icoreplugin.h \
    pluginlinkercore.h

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
