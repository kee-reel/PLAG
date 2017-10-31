
TARGET = COMPortDataSource
TEMPLATE = lib
QT += widgets serialport

SOURCES += \
    comportdatasource.cpp \
    serialporthandler.cpp

HEADERS +=\
    icomportdatasource.h \
    comportdatasource.h \
    serialporthandler.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
