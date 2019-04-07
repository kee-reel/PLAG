#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskSketchManagerView
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QWIDGET

include(../../Common/BuildInfo.pri)

SOURCES += \
    galleryform.cpp \
    paintwidget.cpp \
    galleryitem.cpp \
    qimageitemdelegate.cpp \
    tasksketchmanagerview.cpp

HEADERS += \
    galleryform.h \
    paintwidget.h \
    galleryitem.h \
    qimageitemdelegate.h \
    tasksketchmanagerview.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    galleryform.ui \
    form.ui

RESOURCES += \
    res.qrc
