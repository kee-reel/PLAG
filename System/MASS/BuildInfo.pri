CONFIG += c++11 plugin

DESTDIR = ../../System/MASS/Modules

unix {
    target.path = /usr/lib
    INSTALLS += target
}
