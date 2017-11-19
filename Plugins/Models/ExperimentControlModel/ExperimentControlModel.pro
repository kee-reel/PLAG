
TARGET = ExperimentControlModel
TEMPLATE = lib
QT += widgets serialport serialbus charts

SOURCES += \
    experimentcontrolmodel.cpp \
    experimentsetup.cpp \
    datachannel.cpp \
    registerspacktablemodel.cpp \
    registervaluesmodel.cpp \
    modbusdevicesmodel.cpp

HEADERS +=\
    iexperimentcontrolmodel.h \
    experimentcontrolmodel.h \
    experimentsetup.h \
    datachannel.h \
    registerspacktablemodel.h \
    registervaluesmodel.h \
    modbusdevicesmodel.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
