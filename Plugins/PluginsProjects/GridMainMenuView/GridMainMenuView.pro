
TARGET = GridMainMenuView
TEMPLATE = lib
QT += widgets

DEFINES += \
    PLUGIN_BASE_QWIDGET

include(../../Common/BuildInfo.pri)

SOURCES += \
    gridmainmenuview.cpp \
    aspectawaregridlayout.cpp \
    uniquepushbutton.cpp

HEADERS += \
    ../../PluginsInterfaces/iuimanager.h \
    gridmainmenuview.h \
    aspectawaregridlayout.h \
    uniquepushbutton.h

DISTFILES += \
    PluginMeta.json \
    MenuGrid.qml


FORMS += \
    form.ui

RESOURCES += \
    res.qrc
