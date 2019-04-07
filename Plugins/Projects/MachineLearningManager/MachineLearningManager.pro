#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MachineLearningManager
TEMPLATE = lib
QT += core script

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    Perceptron/neurallayer.cpp \
    ART/artnetwork.cpp \
    ART/recognitionlayer.cpp \
    ART/comparinglayer.cpp \
    ART/neuron.cpp \
    GeneticAlgorithm/geneticalgorithm.cpp \
    GeneticAlgorithm/chromosome.cpp \
    Perceptron/perceptron.cpp \
    machinelearningmanager.cpp

HEADERS += \
    Perceptron/neurallayer.h \
    Perceptron/parameters.h \
    ART/artnetwork.h \
    ART/recognitionlayer.h \
    ART/comparinglayer.h \
    ART/neuron.h \
    parameters.h \
    GeneticAlgorithm/geneticalgorithm.h \
    GeneticAlgorithm/chromosome.h \
    Perceptron/perceptron.h \
    machinelearningmanager.h

DISTFILES += \
    PluginMeta.json
