#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskListModel
TEMPLATE = lib
QT += widgets

SOURCES += \
    tasktreeitemmodel.cpp \
    treeitem.cpp \
    tasktreepluginmodel.cpp

HEADERS +=\
    ../TaskDBToolPlugin/itaskdbtoolplugin.h \
    ../../System/MASS/interfaces.h \
    tasktreeitemmodel.h \
    itasktreemodel.h \
    treeitem.h \
    tasktreepluginmodel.h

windows{
    DESTDIR = ../../System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}
unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
