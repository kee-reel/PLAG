#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskSketchView
TEMPLATE = lib
QT += widgets

SOURCES += \
    mainform.cpp \
    galleryform.cpp \
    paintwidget.cpp \
    galleryitem.cpp \
    qimageitemdelegate.cpp \
    tasksketchview.cpp

HEADERS +=\
    mainform.h \
    galleryform.h \
    paintwidget.h \
    galleryitem.h \
    qimageitemdelegate.h \
    tasksketchview.h

include(../../BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

FORMS += \
    mainform.ui \
    galleryform.ui

RESOURCES += \
    res.qrc
