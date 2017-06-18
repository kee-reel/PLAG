windows{
    debug{
        DESTDIR = ../../build-MASS-Desktop_Qt_5_5_1_GCC_32bit-Debug/Modules
    }
    !debug{
        DESTDIR = ../../build-MASS-Desktop_Qt_5_5_1_GCC_32bit-Release/Modules
    }
}

android{
    debug{
        DESTDIR = ../../System/build-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-MASS-Debug/Modules
    }
    !debug{
        DESTDIR = ../../System/build-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-MASS-Release/Modules
    }
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
