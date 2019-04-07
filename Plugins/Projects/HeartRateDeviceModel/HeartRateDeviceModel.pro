
TARGET = HeartRateDevice
TEMPLATE = lib
QT += widgets serialport serialbus charts

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    heartratedevice.cpp

HEADERS += \
    heartratedevice.h

DISTFILES += \
    PluginMeta.json
