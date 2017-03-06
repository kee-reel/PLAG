#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = ExtendableDataBaseManagerPlugin
TEMPLATE = lib
QT += core sql

windows{
    DESTDIR = ../../System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json

HEADERS += \
    extendabledatabasemanagerplugin.h \
    iextendabledatabasemanagerplugin.h \
    tablehandler.h

SOURCES += \
    extendabledatabasemanagerplugin.cpp \
    tablehandler.cpp