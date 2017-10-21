
TARGET = COMPortDataSource
TEMPLATE = lib
QT += widgets serialport

SOURCES += \
    comportdatasource.cpp \
    qserialporthandler.cpp

HEADERS +=\
    icomportdatasource.h \
    comportdatasource.h \
    qserialporthandler.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
