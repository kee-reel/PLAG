#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PomodoroModel
TEMPLATE = lib
QT += widgets

SOURCES += \
    pomodoromodel.cpp

HEADERS +=\
    ipomodoromodel.h \
    pomodoromodel.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
