
TARGET = NotificationManagerModel
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

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
    qextendedtimer.h

DISTFILES += \
    PluginMeta.json
