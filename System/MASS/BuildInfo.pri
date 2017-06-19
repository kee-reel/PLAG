windows{
    debug{
        DESTDIR = ../../build-MASS-Desktop_Qt_5_5_1_GCC_32bit-Debug/Modules
    }
<<<<<<< HEAD
    !debug{
        DESTDIR = ../../build-MASS-Desktop_Qt_5_5_1_GCC_32bit-Release/Modules
=======
    else
    {
        DESTDIR = ../../System/build-Desktop_Qt_5_8_0_MinGW_32bit-MASS-Release/Modules
>>>>>>> 227ec9f1541046b734c2a5bdaa7a0cefcb119ec7
    }
}

android{
    debug{
        DESTDIR = ../../System/build-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-MASS-Debug/Modules
    }
<<<<<<< HEAD
    !debug{
        DESTDIR = ../../System/build-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-MASS-Release/Modules
=======
    else
    {
        DESTDIR = C:\Users\Curunir\Desktop\MASS\System\build-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-MASS-Release\Modules
>>>>>>> 227ec9f1541046b734c2a5bdaa7a0cefcb119ec7
    }
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
