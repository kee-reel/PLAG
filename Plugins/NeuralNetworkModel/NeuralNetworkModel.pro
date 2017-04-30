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
    neurallayer.cpp \
    artnetwork.cpp \
    Perceptron/artnetwork.cpp \
    Perceptron/neurallayer.cpp \
    Perceptron/neuron.cpp \
    ART/artnetwork.cpp \
    Perceptron/perceptron.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    neuralnetworkmodel.h \
    ineuralnetworkmodel.h \
    neuralnetwork.h \
    neurallayer.h \
    artnetwork.h \
    Perceptron/artnetwork.h \
    Perceptron/neurallayer.h \
    Perceptron/neuron.h \
    ART/artnetwork.h \
    Perceptron/perceptron.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
