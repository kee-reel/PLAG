
TARGET = ExperimentControlView
TEMPLATE = lib
QT += widgets

SOURCES += \
    experimentcontrolview.cpp \
    qcustomplot.cpp

HEADERS +=\
    iexperimentcontrolview.h \
    experimentcontrolview.h \
    qcustomplot.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)

FORMS += \
    form.ui
