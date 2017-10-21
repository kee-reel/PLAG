
TARGET = HardwareDataManager
TEMPLATE = lib
QT += widgets serialport

SOURCES += \
    hardwaredatamanager.cpp \
    devicedatahandler.cpp

HEADERS +=\
    ihardwaredatamanager.h \
    hardwaredatamanager.h \
    devicedatahandler.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
