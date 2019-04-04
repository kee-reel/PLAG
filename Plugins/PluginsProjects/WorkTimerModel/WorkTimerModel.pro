
TARGET = WorkTimerModel
TEMPLATE = lib
QT += widgets charts

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    worktimermodel.cpp \
    datachartwidget.cpp \
    mainwindow.cpp \
    sessiondata.cpp

HEADERS +=\
    worktimermodel.h \
    datachartwidget.h \
    mainwindow.h \
    sessiondata.h

DISTFILES += \
    PluginMeta.json
