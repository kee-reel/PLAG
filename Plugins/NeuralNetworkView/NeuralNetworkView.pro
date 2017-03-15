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

windows{
    DESTDIR = ../../System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
