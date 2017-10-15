
TARGET = NotificationManagerModel
TEMPLATE = lib
QT += widgets

android{
QT += androidextras
}

SOURCES += \
    notificationmanagermodel.cpp \
    qextendedtimer.cpp

HEADERS +=\
    notificationmanagermodel.h \
    inotificationmanagermodel.h \
    qextendedtimer.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
