#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskSketchView
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QWIDGET

include(../../Common/BuildInfo.pri)

SOURCES += \
    galleryform.cpp \
    paintwidget.cpp \
    galleryitem.cpp \
    qimageitemdelegate.cpp \
    tasksketchview.cpp

HEADERS += \
    ../../PluginsInterfaces/itasktreemodel.h \
    galleryform.h \
    paintwidget.h \
    galleryitem.h \
    qimageitemdelegate.h \
    tasksketchview.h

DISTFILES += \
    PluginMeta.json

FORMS += \
    galleryform.ui \
    form.ui

RESOURCES += \
    res.qrc
