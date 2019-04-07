TARGET = UserTaskManager
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

HEADERS += \
    usertaskmanager.h

SOURCES += \
    usertaskmanager.cpp

DISTFILES += \
    PluginMeta.json \
    RelationsInclude.pri
