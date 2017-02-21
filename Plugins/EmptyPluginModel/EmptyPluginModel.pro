#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T20:08:55
#
#-------------------------------------------------
TARGET = EmptyPluginModel
TEMPLATE = lib
QT += core

SOURCES += \
    emptypluginmodel.cpp

HEADERS += \
    ../../System/MASS/interfaces.h \
    emptypluginmodel.h \
    iemptypluginmodel.h

windows{
    DESTDIR = C:/Users/Curunir/Desktop/Qt/System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PluginMeta.json
