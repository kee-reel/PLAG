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
    x.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    neuralnetworkmodel.h \
    ineuralnetworkmodel.h \
    neuralnetwork.h \
    neurallayer.h \
    x.h

windows{
    DESTDIR = ../../System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}
unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
