TARGET = TaskListModel
TEMPLATE = lib
QT += widgets

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

HEADERS += \
    tasktreemodel.h \
    itasktreemodel.h

SOURCES += \
    tasktreemodel.cpp
