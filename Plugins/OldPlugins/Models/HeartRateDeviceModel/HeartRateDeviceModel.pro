
TARGET = HeartRateDeviceModel
TEMPLATE = lib
QT += widgets serialport serialbus charts

SOURCES += \
    heartratedevicemodel.cpp

HEADERS +=\
    iheartratedevicemodel.h \
    heartratedevicemodel.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
