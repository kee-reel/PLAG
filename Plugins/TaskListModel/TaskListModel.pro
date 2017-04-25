#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskListModel
TEMPLATE = lib
QT += widgets

SOURCES += \
    tasktreemodel.cpp

HEADERS +=\
    itasktreemodel.h \
    tasktreemodel.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
