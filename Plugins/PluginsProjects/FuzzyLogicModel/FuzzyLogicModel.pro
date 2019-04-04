
TARGET = FuzzyLogicModel
TEMPLATE = lib
QT += widgets

DEFINES += PLUGIN_BASE_QOBJECT

include(../../PluginsCommon/BuildInfo.pri)

#DEFINES -= ERROR

SOURCES += \
    fuzzylogicmodel.cpp \
    membershipfunc.cpp \
    fuzzyset.cpp \
    fuzzyrule.cpp \
    outputvariable.cpp \
    inputvariable.cpp \
    fuzzysetunion.cpp

HEADERS +=\
    fuzzylogicmodel.h \
    membershipfunc.h \
    fuzzyset.h \
    fuzzyrule.h \
    outputvariable.h \
    inputvariable.h \
    fuzzysetunion.h

DISTFILES += \
    PluginMeta.json
