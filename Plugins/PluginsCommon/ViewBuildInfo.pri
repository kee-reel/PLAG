# Common build info for plugins
include(BuildInfo.pri)

# BuildInfo for view plugins
HEADERS += \
    $$PWD/view_plugin_base.h

SOURCES += \
    $$PWD/view_plugin_base.cpp
