#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = EmptyModule
TEMPLATE = lib
QT += widgets sql
DEFINES += EMPTYMODULE_LIBRARY

SOURCES += \
    mainwindow.cpp \
    emptymodule.cpp

HEADERS +=\
    mainwindow.h \
    emptymodule.h \
    idbtoolplugin.h \
    idbmanagerplugin.h \
    pluginstructs.h \
    ipluginmodel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
