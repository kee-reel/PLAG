# For nice folders organisation
include(common.pri)

DESTDIR = $PWD/Modules

unix {
    target.path = /usr/lib
    INSTALLS += target
}
