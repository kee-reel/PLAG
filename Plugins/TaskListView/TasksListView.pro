#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskListView
TEMPLATE = lib
QT += widgets

SOURCES += \
    tasklistview.cpp

HEADERS +=\
    ../TaskListModel/itasklistmodel.h \
    tasklistview.h \
    ../../System/TimeKeeper/interfaces.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
