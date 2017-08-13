
TARGET = AndroidNotificationModel
TEMPLATE = lib
QT += widgets androidextras

SOURCES += \
    androidnotificationmodel.cpp \
    notificationclient.cpp

HEADERS +=\
    iandroidnotificationmodel.h \
    androidnotificationmodel.h \
    notificationclient.h

DISTFILES += \
    PluginMeta.json \
    AndroidManifest.xml \
    NotificationClient.java

include(../../System/MASS/BuildInfo.pri)
