#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuModel
TEMPLATE = lib
QT += widgets sql

include(../../BuildInfo.pri)

SOURCES += \
    mainmenumodelplugin.cpp \
    pluginlinker.cpp \
    pluginhandler.cpp \
    widgetstack.cpp

HEADERS +=\
    imainmenumodule.h \
    mainmenumodelplugin.h \
    pluginlinker.h \
    pluginhandler.h \
    widgetstack.h

DISTFILES += \
    PluginMeta.json
