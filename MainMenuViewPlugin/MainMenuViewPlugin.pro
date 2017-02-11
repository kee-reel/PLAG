#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = MainMenuViewPlugin
TEMPLATE = lib
QT += widgets sql

SOURCES += \
    draggablebutton.cpp \
    mainwindow.cpp \
    mainmenupluginview.cpp

HEADERS +=\
    draggablebutton.h \
    mainwindow.h \
    mainmenupluginview.h \
    ../MainMenuModelPlugin/imainmenumodule.h \
    ../TimeKeeper/interfaces.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
