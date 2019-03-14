
TARGET = ExperimentControlModel
TEMPLATE = lib
QT += widgets serialport serialbus charts jsonserializer

SOURCES += \
    experimentcontrolmodel.cpp \
    registerspacktablemodel.cpp \
    modbusdevicesmodel.cpp \
    registerspackhandler.cpp

HEADERS +=\
    iexperimentcontrolmodel.h \
    experimentcontrolmodel.h \
    registerspacktablemodel.h \
    modbusdevicesmodel.h \
    registerspackhandler.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
