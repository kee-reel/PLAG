CONFIG += c++11 plugin

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
        DESTDIR = ../../System/MASS/Modules
    }
    else
    {
        DESTDIR = ../../System/MASS/Modules
    }
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
