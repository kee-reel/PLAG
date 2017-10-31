
TARGET = CommonArduinoProtocolModel
TEMPLATE = lib
QT += widgets

SOURCES += \
    commonarduinoprotocolmodel.cpp

HEADERS +=\
    icommonarduinoprotocolmodel.h \
    commonarduinoprotocolmodel.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)