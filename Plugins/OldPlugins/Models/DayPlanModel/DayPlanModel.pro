
TARGET = DayPlanModel
TEMPLATE = lib
QT += widgets

SOURCES += \
    dayplanmodel.cpp

HEADERS +=\
    idayplanmodel.h \
    dayplanmodel.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)