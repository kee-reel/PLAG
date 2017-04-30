#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PomodoroView
TEMPLATE = lib
QT += widgets multimedia

SOURCES += \
    pomodoroview.cpp \
    pomodorobutton.cpp

HEADERS += \
    pomodoroview.h \
    pomodorobutton.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

FORMS += \
    pomodoroview.ui

RESOURCES += \
    res.qrc
