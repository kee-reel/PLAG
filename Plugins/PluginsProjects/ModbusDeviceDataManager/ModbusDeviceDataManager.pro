
TARGET = ModbusDeviceDataManager
TEMPLATE = lib
QT += widgets serialbus serialport gui

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    modbusdevicedatamanager.cpp \
    modbusdevicehandler.cpp

HEADERS +=\
    modbusdevicedatamanager.h \
    modbusdevicehandler.h

DISTFILES += \
    PluginMeta.json
