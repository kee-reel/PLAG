#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuModelPlugin
TEMPLATE = lib
QT += widgets sql

SOURCES += \
    mainmenumodelplugin.cpp

HEADERS +=\
    imainmenumodule.h \
    mainmenumodelplugin.h \
    ../../System/MASS/interfaces.h \
    ../../System/TaskDBToolPlugin/itaskdbtoolplugin.h

windows{
    DESTDIR = C:/Users/Curunir/Desktop/Qt/System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
