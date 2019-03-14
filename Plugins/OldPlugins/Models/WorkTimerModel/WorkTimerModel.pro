
TARGET = WorkTimerModel
TEMPLATE = lib
QT += widgets

SOURCES += \
    worktimermodel.cpp \
    datachartwidget.cpp \
    mainwindow.cpp \
    sessiondata.cpp

HEADERS +=\
    iworktimermodel.h \
    worktimermodel.h \
    datachartwidget.h \
    mainwindow.h \
    sessiondata.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)