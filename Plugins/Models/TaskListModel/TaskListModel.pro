TARGET = TaskListModel
TEMPLATE = lib
QT += widgets

include(../../BuildInfo.pri)

DISTFILES += \
    PluginMeta.json \
    RelationsInclude.pri

HEADERS += \
    tasktreemodel.h \
    itasktreemodel.h

SOURCES += \
    tasktreemodel.cpp
