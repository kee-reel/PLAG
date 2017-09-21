
TARGET = DayPlanView
TEMPLATE = lib
QT += widgets

SOURCES += \
    dayplanview.cpp \
    datetimetypeeditor.cpp

HEADERS +=\
    idayplanview.h \
    dayplanview.h \
    datetimetypeeditor.h

DISTFILES += \
    PluginMeta.json

include(../../System/MASS/BuildInfo.pri)

FORMS += \
    form.ui