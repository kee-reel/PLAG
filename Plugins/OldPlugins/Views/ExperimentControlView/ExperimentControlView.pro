
TARGET = ExperimentControlView
TEMPLATE = lib
QT += widgets charts serialport serialbus

SOURCES += \
    experimentcontrolview.cpp

HEADERS +=\
    iexperimentcontrolview.h \
    experimentcontrolview.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)

FORMS += \
    form.ui
