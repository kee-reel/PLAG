#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskListModel
TEMPLATE = lib
QT += widgets

SOURCES += \
    treeitem.cpp \
    tasktreemodel.cpp \
    treeitemmodel.cpp

HEADERS +=\
    itasktreemodel.h \
    treeitem.h \
    tasktreemodel.h \
    treeitemmodel.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
