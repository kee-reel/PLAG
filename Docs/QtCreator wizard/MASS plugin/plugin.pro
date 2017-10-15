
TARGET = %{CN}
TEMPLATE = lib
QT += widgets

SOURCES += \\
    %{SrcFileName}

HEADERS +=\\
    %{IFileName} \\
    %{HdrFileName}

DISTFILES += \\
    PluginMeta.json

include(../../System/MASS/BuildInfo.pri)