#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PomodoroModel
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    pomodoromodel.cpp

HEADERS +=\
    pomodoromodel.h

DISTFILES += \
    PluginMeta.json
