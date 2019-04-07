
TARGET = NotificationManager
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

android{
QT += androidextras
}

SOURCES += \
    qextendedtimer.cpp \
    win_motificationmanagermodel.cpp \
    android_notificationmanagermodel.cpp \
    common_notificationmanagermodel.cpp

HEADERS +=\
    qextendedtimer.h \
    notificationmanager.h

DISTFILES += \
    PluginMeta.json
