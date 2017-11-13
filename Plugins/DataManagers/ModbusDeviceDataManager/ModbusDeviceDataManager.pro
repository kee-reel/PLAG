
TARGET = ModbusDeviceDataManager
TEMPLATE = lib
QT += widgets serialbus serialport

SOURCES += \
    modbusdevicedatamanager.cpp \
    modbusdevicehandler.cpp

HEADERS +=\
    imodbusdevicedatamanager.h \
    modbusdevicedatamanager.h \
    modbusdevicehandler.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
