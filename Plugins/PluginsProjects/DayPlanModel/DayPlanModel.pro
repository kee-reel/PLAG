
TARGET = DayPlanModel
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    dayplanmodel.cpp

HEADERS +=\
    dayplanmodel.h

DISTFILES += \
    PluginMeta.json
