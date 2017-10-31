
TARGET = ExperimentControlView
TEMPLATE = lib
QT += widgets charts

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
