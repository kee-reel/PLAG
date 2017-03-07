#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuModelPlugin
TEMPLATE = lib
QT += widgets sql

SOURCES += \
    mainmenumodelplugin.cpp \
    pluginlinker.cpp

HEADERS +=\
    imainmenumodule.h \
    mainmenumodelplugin.h \
    ../../System/MASS/rootinterfaces.h \
    pluginlinker.h \
    interfaces.h

windows{
    DESTDIR = ../../System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}

android{
    DESTDIR = ../../System/build-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-MASS-Release/Modules
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
