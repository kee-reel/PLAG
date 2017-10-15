
TARGET = GridMainMenuView
TEMPLATE = lib
QT += widgets

SOURCES += \
    gridmainmenuview.cpp \
    menuitem.cpp \
    aspectawaregridlayout.cpp

HEADERS +=\
    igridmainmenuview.h \
    gridmainmenuview.h \
    menuitem.h \
    aspectawaregridlayout.h

DISTFILES += \
    PluginMeta.json \
    MenuGrid.qml

include(../../BuildInfo.pri)

FORMS += \
    gridmainmenuview.ui

RESOURCES += \
    res.qrc
