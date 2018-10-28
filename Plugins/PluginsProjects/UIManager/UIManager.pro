
TARGET = UIManager
TEMPLATE = lib
QT += widgets

SOURCES += \
    uimanager.cpp

HEADERS += \
    uimanager.h \
    ../../PluginsInterfaces/iuimanager.h

DEFINES += \
    PLUGIN_BASE_QOBJECT
    
DISTFILES += \
    PluginMeta.json

include(../../PluginsCommon/BuildInfo.pri)
