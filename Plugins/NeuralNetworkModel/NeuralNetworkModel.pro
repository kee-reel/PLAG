#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = NeuralNetworkModel
TEMPLATE = lib
QT += core

SOURCES += \
    neuralnetworkmodel.cpp \
    neuralnetwork.cpp \
    neurallayer.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    neuralnetworkmodel.h \
    ineuralnetworkmodel.h \
    neuralnetwork.h \
    neurallayer.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
