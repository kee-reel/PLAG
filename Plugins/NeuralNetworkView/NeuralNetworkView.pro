#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = NeuralNetworkView
TEMPLATE = lib
QT += widgets printsupport

SOURCES += \
    neuralnetworkview.cpp \
    mainform.cpp \
    qcustomplot.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    neuralnetworkview.h \
    mainform.h \
    qcustomplot.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

FORMS += \
    mainform.ui
