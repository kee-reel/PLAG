#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = TaskListView
TEMPLATE = lib
QT += widgets qml quick

SOURCES += \
    tasklistview.cpp \
    mainform.cpp

HEADERS +=\
    ../TaskListModel/itasklistmodel.h \
    tasklistview.h \
    ../../System/MASS/interfaces.h \
    mainform.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json

RESOURCES +=

FORMS += \
    mainform.ui
