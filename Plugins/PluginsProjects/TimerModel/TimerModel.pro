
TARGET = TimerModel
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    timermodel.cpp

HEADERS +=\
    timermodel.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
