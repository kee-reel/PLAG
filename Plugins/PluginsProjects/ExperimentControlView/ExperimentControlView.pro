
TARGET = ExperimentControlView
TEMPLATE = lib
QT += widgets charts serialport serialbus

DEFINES += PLUGIN_BASE_QWIDGET

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    experimentcontrolview.cpp

HEADERS +=\
    experimentcontrolview.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui
