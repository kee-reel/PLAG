#-------------------------------------------------
#
# Project created by QtCreator 2017-01-21T17:03:09
#
#-------------------------------------------------

QT       += widgets sql gui qml quick

TARGET = MASS
TEMPLATE = app
CONFIG += plugin

SOURCES += main.cpp\
    parentwindow.cpp \
    pluginloader.cpp

HEADERS  += \
    parentwindow.h \
    pluginloader.h \
    rootinterface.h

android {
    QT += androidextras

    android-no-sdk {
        target.path = /data/user/qt
        export(target.path)
        INSTALLS += target
    } else:android {
        x86 {
            target.path = /libs/x86
        } else: armeabi-v7a {
            target.path = /libs/armeabi-v7a
        } else {
            target.path = /libs/armeabi
        }
        export(target.path)
        INSTALLS += target
    } else:unix {
        isEmpty(target.path) {
            qnx {
                target.path = /tmp/$${TARGET}/bin
            } else {
                target.path = /opt/$${TARGET}/bin
            }
            export(target.path)
        }
        INSTALLS += target
    }

    export(INSTALLS)

    DISTFILES += \
        android/AndroidManifest.xml \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradlew \
        android/res/values/libs.xml \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew.bat

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

DISTFILES += \
    BuildInfo.pri
