
TARGET = FuzzyLogicModel
TEMPLATE = lib
QT += widgets

DEFINES -= ERROR

SOURCES += \
    fuzzylogicmodel.cpp \
    membershipfunc.cpp \
    fuzzyset.cpp \
    fuzzyrule.cpp \
    outputvariable.cpp \
    inputvariable.cpp \
    fuzzysetunion.cpp

HEADERS +=\
    ifuzzylogicmodel.h \
    fuzzylogicmodel.h \
    membershipfunc.h \
    fuzzyset.h \
    fuzzyrule.h \
    outputvariable.h \
    inputvariable.h \
    fuzzysetunion.h

DISTFILES += \
    PluginMeta.json

include(../../BuildInfo.pri)
