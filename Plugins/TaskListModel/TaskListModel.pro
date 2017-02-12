#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskListModel
TEMPLATE = lib
QT += core

SOURCES += \
    tasklistmodel.cpp

HEADERS +=\
    itasklistmodel.h \
    tasklistmodel.h \
    ../TaskDBToolPlugin/itaskdbtoolplugin.h \
    ../../System/TimeKeeper/interfaces.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
