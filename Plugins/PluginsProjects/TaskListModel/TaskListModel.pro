TARGET = TaskListModel
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

HEADERS += \
    ../../PluginsInterfaces/itasktreemodel.h \
    tasktreemodel.h

SOURCES += \
    tasktreemodel.cpp

DISTFILES += \
    PluginMeta.json \
    RelationsInclude.pri
