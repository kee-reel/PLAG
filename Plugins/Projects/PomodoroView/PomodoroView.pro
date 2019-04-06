#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PomodoroView
TEMPLATE = lib
QT += widgets multimedia

DEFINES += PLUGIN_BASE_QWIDGET

include(../../Common/BuildInfo.pri)

SOURCES += \
    pomodoroview.cpp \
    pomodorobutton.cpp \
    mytreeview.cpp \
    designproxymodel.cpp

HEADERS += \
    pomodoroview.h \
    pomodorobutton.h \
    mytreeview.h \
    designproxymodel.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui

RESOURCES += \
    res.qrc
