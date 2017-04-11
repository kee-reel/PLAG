#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = ARNeuralNetworkView
TEMPLATE = lib
QT += widgets printsupport

SOURCES += \
    mainform.cpp \
    qcustomplot.cpp \
    arneuralnetworkview.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    mainform.h \
    qcustomplot.h \
    arneuralnetworkview.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

FORMS += \
    mainform.ui

RESOURCES += \
    res.qrc
