
TARGET = COMPortDataManager
TEMPLATE = lib
QT += widgets serialport

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    serialporthandler.cpp \
    comportdatamanager.cpp

HEADERS +=\
    serialporthandler.h \
    comportdatamanager.h

DISTFILES += \
    PluginMeta.json
