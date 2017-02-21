#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = DatabaseManagerModule
TEMPLATE = lib
QT += core sql

SOURCES += \
    cipherdatabasesourceplugin.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    cipherdatabasesourceplugin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
