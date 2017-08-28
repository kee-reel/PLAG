#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuModelPlugin
TEMPLATE = lib
QT += widgets sql

SOURCES += \
    mainmenumodelplugin.cpp \
    pluginlinker.cpp \
    pluginhandler.cpp \
    widgetstack.cpp

HEADERS +=\
    imainmenumodule.h \
    mainmenumodelplugin.h \
    pluginlinker.h \
    interfaces.h \
    pluginhandler.h \
    widgetstack.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
