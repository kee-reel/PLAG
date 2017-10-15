 #-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuView
TEMPLATE = lib
QT += widgets

SOURCES += \
    mainmenupluginview.cpp \
    mainform.cpp \
    menuitem.cpp

HEADERS +=\
    mainmenupluginview.h \
    mainform.h \
    menuitem.h

include(../../BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

RESOURCES += \
    mainwindow.qrc

FORMS += \
    mainform.ui
