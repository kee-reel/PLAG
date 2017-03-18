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
    pluginlinker.cpp

HEADERS +=\
    imainmenumodule.h \
    mainmenumodelplugin.h \
    ../../System/MASS/rootinterfaces.h \
    pluginlinker.h \
    interfaces.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
