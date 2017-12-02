CONFIG += c++11 plugin

DESTDIR = $PWD/Modules

unix {
    target.path = /usr/lib
    INSTALLS += target
}
