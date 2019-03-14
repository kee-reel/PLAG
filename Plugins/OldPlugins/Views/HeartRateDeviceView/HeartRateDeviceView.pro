
TARGET = HeartRateDeviceView
TEMPLATE = lib
QT += widgets

SOURCES += \
    heartratedeviceview.cpp

HEADERS +=\
    iheartratedeviceview.h \
    heartratedeviceview.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)

FORMS += \
    form.ui