#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = NeuralNetworkModel
TEMPLATE = lib
QT += core script

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    neuralnetworkmodel.cpp \
    Perceptron/neurallayer.cpp \
    ART/artnetwork.cpp \
    ART/recognitionlayer.cpp \
    ART/comparinglayer.cpp \
    ART/neuron.cpp \
    Perceptron/perceptronnetwork.cpp \
    GeneticAlgorithm/geneticalgorithm.cpp \
    GeneticAlgorithm/chromosome.cpp

HEADERS += \
    neuralnetworkmodel.h \
    Perceptron/neurallayer.h \
    Perceptron/parameters.h \
    ART/artnetwork.h \
    ART/recognitionlayer.h \
    ART/comparinglayer.h \
    ART/neuron.h \
    parameters.h \
    Perceptron/perceptronnetwork.h \
    GeneticAlgorithm/geneticalgorithm.h \
    GeneticAlgorithm/chromosome.h

DISTFILES += \
    PluginMeta.json
