#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuModel
TEMPLATE = lib
QT += core widgets


SOURCES += \
    mainmenumodelplugin.cpp

HEADERS +=\
    mainmenumodelplugin.h \
    ../../PluginsInterfaces/imainmenumodule.h \
    ../../PluginsInterfaces/ipluginlinker.h

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
