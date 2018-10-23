#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuModel
TEMPLATE = lib
QT += core widgets

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    mainmenumodelplugin.cpp \
    pluginlinker.cpp \
    widgetstack.cpp \
    linkeritem.cpp

HEADERS +=\
    mainmenumodelplugin.h \
    pluginlinker.h \
    widgetstack.h \
    iplugin.h \
    linkeritem.h

DISTFILES += \
    PluginMeta.json
