 #-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuViewPlugin
TEMPLATE = lib
QT += widgets

SOURCES += \
    draggablebutton.cpp \
    mainwindow.cpp \
    mainmenupluginview.cpp

HEADERS +=\
    draggablebutton.h \
    mainwindow.h \
    mainmenupluginview.h \
    ../MainMenuModelPlugin/imainmenumodule.h
windows{
    DESTDIR = ../../System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json

RESOURCES += \
    mainwindow.qrc
