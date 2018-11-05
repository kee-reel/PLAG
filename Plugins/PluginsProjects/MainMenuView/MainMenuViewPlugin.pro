 #-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuView
TEMPLATE = lib
QT += widgets

DEFINES += \
    PLUGIN_BASE_QWIDGET

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    mainmenupluginview.cpp \
    menuitem.cpp

HEADERS +=\
    mainmenupluginview.h \
    menuitem.h

DISTFILES += \
    PluginMeta.json

RESOURCES += \
    mainwindow.qrc

FORMS += \
    form.ui
