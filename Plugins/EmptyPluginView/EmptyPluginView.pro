#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = EmptyPluginView
TEMPLATE = lib
QT += widgets

SOURCES += \
    emptypluginview.cpp \
    mainwindow.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    iemptypluginmodel.h \
    emptypluginview.h \
    mainwindow.h

windows{
    DESTDIR = C:/Users/Curunir/Desktop/Qt/System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
