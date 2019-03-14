
TARGET = TimerModel
TEMPLATE = lib
QT += widgets

SOURCES += \
    timermodel.cpp

HEADERS +=\
    itimermodel.h \
    timermodel.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)