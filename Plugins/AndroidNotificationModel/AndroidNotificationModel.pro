
TARGET = AndroidNotificationModel
TEMPLATE = lib
QT += widgets androidextras

SOURCES += \
    androidnotificationmodel.cpp

HEADERS +=\
    iandroidnotificationmodel.h \
    androidnotificationmodel.h

DISTFILES += \
    PluginMeta.json

include(../../System/MASS/BuildInfo.pri)
