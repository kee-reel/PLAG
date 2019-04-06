
TARGET = UIManager
TEMPLATE = lib
QT += widgets

SOURCES += \
    uimanager.cpp \
    uielement.cpp

HEADERS += \
    uimanager.h \
    ../../PluginsInterfaces/ipluginlinker.h \
    ../../PluginsInterfaces/iuimanager.h \
    uielement.h

DEFINES += \
    PLUGIN_BASE_QOBJECT
    
DISTFILES += \
    PluginMeta.json

include(../../Common/BuildInfo.pri)
