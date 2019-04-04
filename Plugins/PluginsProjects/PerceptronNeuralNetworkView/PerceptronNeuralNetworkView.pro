#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = PerceptronNetworkViewPlugin
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QWIDGET

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    qcustomplot.cpp \
    perceptronneuralnetworkview.cpp

HEADERS += \
    qcustomplot.h \
    perceptronneuralnetworkview.h


DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui

RESOURCES += \
    res.qrc
