#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = EmptyPluginView
TEMPLATE = lib
QT += widgets

SOURCES += \
    emptypluginview.cpp

HEADERS +=\
    ../TimeKeeper/interfaces.h \
    iemptypluginmodel.h \
    emptypluginview.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
