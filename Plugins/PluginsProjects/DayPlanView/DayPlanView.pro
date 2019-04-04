
TARGET = DayPlanView
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QWIDGET

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    dayplanview.cpp \
    datetimetypeeditor.cpp \
    mytreeview.cpp \
    designproxymodel.cpp

HEADERS +=\
    dayplanview.h \
    datetimetypeeditor.h \
    mytreeview.h \
    designproxymodel.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    form.ui
