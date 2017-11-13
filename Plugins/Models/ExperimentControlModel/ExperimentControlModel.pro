
TARGET = ExperimentControlModel
TEMPLATE = lib
QT += widgets serialport serialbus charts

SOURCES += \
    experimentcontrolmodel.cpp \
    experimentsetup.cpp \
    datachannel.cpp

HEADERS +=\
    iexperimentcontrolmodel.h \
    experimentcontrolmodel.h \
    experimentsetup.h \
    datachannel.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
