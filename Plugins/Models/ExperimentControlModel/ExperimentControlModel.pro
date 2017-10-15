
TARGET = ExperimentControlModel
TEMPLATE = lib
QT += widgets

SOURCES += \
    experimentcontrolmodel.cpp

HEADERS +=\
    iexperimentcontrolmodel.h \
    experimentcontrolmodel.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
