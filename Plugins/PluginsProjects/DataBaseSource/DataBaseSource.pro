#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = DataBaseSource
TEMPLATE = lib
QT += core sql

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

SOURCES += \
    databasesource.cpp

HEADERS += \
    idatabasesource.h \
    databasesource.h \
    ../../PluginsInterfaces/idatabasesource.h

DISTFILES += \
    PluginMeta.json
