
TARGET = DayPlanView
TEMPLATE = lib
QT += widgets

SOURCES += \
    dayplanview.cpp

HEADERS +=\
    idayplanview.h \
    dayplanview.h

DISTFILES += \
    PluginMeta.json

include(../../System/MASS/BuildInfo.pri)

FORMS += \
    form.ui