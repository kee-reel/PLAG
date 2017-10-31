
TARGET = ExperimentControlModel
TEMPLATE = lib
QT += widgets charts

SOURCES += \
    experimentcontrolmodel.cpp

HEADERS +=\
    iexperimentcontrolmodel.h \
    experimentcontrolmodel.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
