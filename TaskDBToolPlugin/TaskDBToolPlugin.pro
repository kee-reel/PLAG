#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskDBToolPlugin
TEMPLATE = lib
QT += core sql

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json

HEADERS += \
    idbmanagerplugin.h \
    idbtoolplugin.h \
    taskdbtoolplugin.h \
    itaskdbtoolplugin.h

SOURCES += \
    taskdbtoolplugin.cpp
