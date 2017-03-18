windows{
    release{
        DESTDIR = ../../System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
    }
    debug{
        DESTDIR = ../../System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Debug/Modules
    }
}

android{
    release{
        DESTDIR = ../../System/build-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-MASS-Release/Modules
    }
    debug{
        DESTDIR = ../../System/build-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-MASS-Debug/Modules
    }
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
