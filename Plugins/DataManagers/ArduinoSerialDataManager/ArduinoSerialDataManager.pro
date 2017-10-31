
TARGET = ArduinoSerialDataManager
TEMPLATE = lib
QT += widgets serialport

SOURCES += \
    arduinoserialdatamanager.cpp

HEADERS +=\
    iarduinoserialdatamanager.h \
    arduinoserialdatamanager.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
