
TARGET = FuzzyLogicManager
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../Common/BuildInfo.pri)

#DEFINES -= ERROR

SOURCES += \
    membershipfunc.cpp \
    fuzzyset.cpp \
    fuzzyrule.cpp \
    outputvariable.cpp \
    inputvariable.cpp \
    fuzzysetunion.cpp \
    fuzzylogicmanager.cpp

HEADERS +=\
    membershipfunc.h \
    fuzzyset.h \
    fuzzyrule.h \
    outputvariable.h \
    inputvariable.h \
    fuzzysetunion.h \
    fuzzylogicmanager.h

DISTFILES += \
    PluginMeta.json
