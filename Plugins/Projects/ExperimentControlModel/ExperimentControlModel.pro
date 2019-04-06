
TARGET = ExperimentControlModel
TEMPLATE = lib
QT += widgets serialport serialbus charts jsonserializer

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    experimentcontrolmodel.cpp \
    registerspacktablemodel.cpp \
    modbusdevicesmodel.cpp \
    registerspackhandler.cpp

HEADERS +=\
    experimentcontrolmodel.h \
    registerspacktablemodel.h \
    modbusdevicesmodel.h \
    registerspackhandler.h

DISTFILES += \
    PluginMeta.json
