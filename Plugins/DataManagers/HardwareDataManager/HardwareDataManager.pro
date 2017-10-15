
TARGET = HardwareDataManager
TEMPLATE = lib
QT += widgets

SOURCES += \
    hardwaredatamanager.cpp

HEADERS +=\
    ihardwaredatamanager.h \
    hardwaredatamanager.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
