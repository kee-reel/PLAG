#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskSketchModel
TEMPLATE = lib
QT += widgets

SOURCES += \
    tasksketchmodel.cpp \
    rawimagedelegate.cpp

HEADERS +=\
    itasksketchmodel.h \
    tasksketchmodel.h \
    rawimagedelegate.h

include(../../BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
