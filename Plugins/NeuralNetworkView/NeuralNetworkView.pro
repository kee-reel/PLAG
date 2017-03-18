#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = NeuralNetworkView
TEMPLATE = lib
QT += widgets

SOURCES += \
    mainwindow.cpp \
    neuralnetworkview.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    mainwindow.h \
    neuralnetworkview.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json
