#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PerceptronNetworkViewPlugin
TEMPLATE = lib
QT += widgets

SOURCES += \
    mainform.cpp \
    qcustomplot.cpp \
    perceptronneuralnetworkview.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    mainform.h \
    qcustomplot.h \
    perceptronneuralnetworkview.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

FORMS += \
    mainform.ui

RESOURCES += \
    res.qrc
