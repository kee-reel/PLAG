#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuModel
TEMPLATE = lib
QT += core widgets


SOURCES += \
    mainmenumodelplugin.cpp \
    pluginlinker.cpp \
    widgetstack.cpp \
    linkeritem.cpp

HEADERS +=\
    mainmenumodelplugin.h \
    pluginlinker.h \
    widgetstack.h \
    linkeritem.h \
    ../../PluginsInterfaces/imainmenumodule.h

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
