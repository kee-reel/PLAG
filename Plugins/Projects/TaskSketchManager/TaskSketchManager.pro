#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskSketchManager
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    rawimagedelegate.cpp \
    tasksketchmanager.cpp

HEADERS +=\
    rawimagedelegate.h \
    tasksketchmanager.h

DISTFILES += \
    PluginMeta.json
