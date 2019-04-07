
TARGET = ModbusDataReader
TEMPLATE = lib
QT += widgets serialport serialbus charts jsonserializer

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    registerspacktablemodel.cpp \
    registerspackhandler.cpp \
    modbusdevicesmodel.cpp \
    modbusdatareader.cpp

HEADERS +=\
    registerspacktablemodel.h \
    modbusdevicesmodel.h \
    registerspackhandler.h \
    modbusdatareader.h

DISTFILES += \
    PluginMeta.json
