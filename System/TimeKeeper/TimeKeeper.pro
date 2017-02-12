#-------------------------------------------------
#
# Project created by QtCreator 2017-01-21T17:03:09
#
#-------------------------------------------------

QT       += widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeKeeper
TEMPLATE = app
CONFIG += plugin release

SOURCES += main.cpp\
    pluginmanager.cpp \
    parentwindow.cpp

HEADERS  += \
    pluginmanager.h \
    mainplugininterface.h \
    parentwindow.h \
    interfaces.h

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

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        C:/Users/Curunir/Desktop/Qt/TimeKeeper/../build-DatabaseManagerModule-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-Release/libDatabaseManagerModule.so \
        C:/Users/Curunir/Desktop/Qt/TimeKeeper/../build-EmptyPluginModel-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-Release/libEmptyPluginModel.so \
        C:/Users/Curunir/Desktop/Qt/TimeKeeper/../build-EmptyPluginView-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-Release/libEmptyPluginView.so \
        C:/Users/Curunir/Desktop/Qt/TimeKeeper/../build-MainMenuModelPlugin-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-Release/libMainMenuModelPlugin.so \
        C:/Users/Curunir/Desktop/Qt/TimeKeeper/../build-MainMenuViewPlugin-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-Release/libMainMenuViewPlugin.so \
        C:/Users/Curunir/Desktop/Qt/TimeKeeper/../build-TaskDBToolPlugin-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-Release/libTaskDBToolPlugin.so \
        C:/Users/Curunir/Desktop/Qt/TimeKeeper/../../QtCipherSqlitePlugin/build-sqlitecipher-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-Release/libc.so \
        C:/Users/Curunir/Desktop/Qt/TimeKeeper/../../QtCipherSqlitePlugin/build-sqlitecipher-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-Release/libsqlitecipher.so \
        C:/Users/Curunir/Desktop/Qt/TimeKeeper/../build-TaskListModel-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-Release/libTaskListModel.so \
        $$PWD/../build-TasksListView-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-Release/libTaskListView.so
}
