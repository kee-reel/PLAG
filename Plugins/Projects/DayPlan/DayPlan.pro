
TARGET = DayPlan
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

SOURCES += \
    dayplan.cpp

HEADERS += \
    dayplan.h

DISTFILES += \
    PluginMeta.json
