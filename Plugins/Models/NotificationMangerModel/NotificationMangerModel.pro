
TARGET = NotificationManagerModel
TEMPLATE = lib
QT += widgets

android{
QT += androidextras
}

SOURCES += \
    qextendedtimer.cpp \
    win_motificationmanagermodel.cpp \
    android_notificationmanagermodel.cpp \
    common_notificationmanagermodel.cpp

HEADERS +=\
    notificationmanagermodel.h \
    inotificationmanagermodel.h \
    qextendedtimer.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
