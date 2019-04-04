
TARGET = HeartRateDeviceView
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QWIDGET

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    heartratedeviceview.cpp

HEADERS += \
    heartratedeviceview.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui
