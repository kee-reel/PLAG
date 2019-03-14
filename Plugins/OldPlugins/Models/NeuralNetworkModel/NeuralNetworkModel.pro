#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = NeuralNetworkModel
TEMPLATE = lib
QT += core script

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
    ../../System/MASS/interfaces.h \
    neuralnetworkmodel.h \
    ineuralnetworkmodel.h \
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

include(../../BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
