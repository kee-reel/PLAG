#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = EmptyPluginModel
TEMPLATE = lib
QT += core

SOURCES += \
    emptypluginmodel.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    emptypluginmodel.h \
    iemptypluginmodel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
