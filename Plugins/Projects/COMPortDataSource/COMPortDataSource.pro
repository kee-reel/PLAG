
TARGET = COMPortDataSource
TEMPLATE = lib
QT += widgets serialport

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    comportdatasource.cpp \
    serialporthandler.cpp

HEADERS +=\
    icomportdatasource.h \
    comportdatasource.h \
    serialporthandler.h

DISTFILES += \
    PluginMeta.json
