
TARGET = DayPlanModel
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    dayplanmodel.cpp

HEADERS +=\
    dayplanmodel.h

DISTFILES += \
    PluginMeta.json
