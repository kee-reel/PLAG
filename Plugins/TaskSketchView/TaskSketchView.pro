#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskSketchView
TEMPLATE = lib
QT += widgets

SOURCES += \
    tasklistview.cpp \
    mainform.cpp \
    galleryform.cpp \
    paintwidget.cpp \
    galleryitem.cpp

HEADERS +=\
    tasklistview.h \
    mainform.h \
    galleryform.h \
    paintwidget.h \
    galleryitem.h

include(../../System/MASS/BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

FORMS += \
    mainform.ui \
    galleryform.ui

RESOURCES += \
    res.qrc
