
TARGET = COMPortDataSource
TEMPLATE = lib
QT += widgets serialport

SOURCES += \
    comportdatasource.cpp \
    devicepin.cpp

HEADERS +=\
    icomportdatasource.h \
    comportdatasource.h \
    devicepin.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
