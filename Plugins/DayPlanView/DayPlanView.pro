
TARGET = DayPlanView
TEMPLATE = lib
QT += widgets

SOURCES += \
    dayplanview.cpp \
    datetimetypeeditor.cpp \
    mytreeview.cpp \
    designproxymodel.cpp

HEADERS +=\
    idayplanview.h \
    dayplanview.h \
    datetimetypeeditor.h \
    mytreeview.h \
    designproxymodel.h

DISTFILES += \
    PluginMeta.json

include(../../System/MASS/BuildInfo.pri)

FORMS += \
    form.ui