# For nice folders organisation
include(common.pri)

# Only for plugins
CONFIG += plugin
DESTDIR = $${PWD}/../../Application/Plugins

HEADERS += \
    $$PWD/iplugin.h \
    $$PWD/plugin_base.h

SOURCES += \
    $$PWD/plugin_base.cpp \
    $$PWD/plugin_base_qobject.cpp \
    $$PWD/plugin_base_qwidget.cpp
