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
    addform.cpp

HEADERS +=\
    tasklistview.h \
    mainform.h \
    addform.h

windows{
    DESTDIR = ../../System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json

FORMS += \
    mainform.ui \
    addform.ui
