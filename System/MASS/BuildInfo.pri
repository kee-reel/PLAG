CONFIG += c++11

windows{
    debug{
        DESTDIR = ../../System/MASS/Modules
    }
    else
    {
        DESTDIR = ../../System/MASS/Modules
    }
}

linux{
    debug{
        DESTDIR = ../../System/MASS/Modules
    }
    else
    {
        DESTDIR = ../../System/MASS/Modules
    }
}

android{
    debug{
        DESTDIR = ../../System/build-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-MASS-Debug/Modules
    }
    else
    {
        DESTDIR = C:\Users\Curunir\Desktop\MASS\System\build-Android_armeabi_v7a_GCC_4_9_Qt_5_8_0-MASS-Release\Modules
    }
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
