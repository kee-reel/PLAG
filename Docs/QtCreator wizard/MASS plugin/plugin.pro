
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

include(../../BuildInfo.pri)