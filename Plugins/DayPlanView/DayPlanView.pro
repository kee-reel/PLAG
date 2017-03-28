#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = DayPlanView
TEMPLATE = lib
QT += widgets

SOURCES += \
    tasklistview.cpp \
    mainform.cpp \
    galleryform.cpp

HEADERS +=\
    tasklistview.h \
    mainform.h \
    galleryform.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

FORMS += \
    mainform.ui \
    galleryform.ui

RESOURCES += \
    res.qrc
