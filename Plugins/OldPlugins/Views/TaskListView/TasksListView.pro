#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskListView
TEMPLATE = lib
QT += widgets

SOURCES += \
    tasklistview.cpp \
    mainform.cpp \
    addform.cpp \
    designproxymodel.cpp \
    mytreeview.cpp

HEADERS +=\
    tasklistview.h \
    mainform.h \
    addform.h \
    designproxymodel.h \
    mytreeview.h

include(../../BuildInfo.pri)

DISTFILES += \
    PluginMeta.json

FORMS += \
    mainform.ui \
    addform.ui

RESOURCES += \
    res.qrc
