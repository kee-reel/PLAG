
TARGET = %{CN}
TEMPLATE = lib
QT += widgets

SOURCES += \\
    %{SrcFileName}

HEADERS += \\
    %{HdrFileName}

DEFINES += \\
@if '%{PluginType}' === 'QObject'
    PLUGIN_BASE_QOBJECT
@elsif '%{PluginType}' === 'QWidget'
    PLUGIN_BASE_QWIDGET
@elsif '%{PluginType}' === 'QWidget with QML'
    PLUGIN_BASE_QWIDGET_QML
@endif
    
DISTFILES += \\
    PluginMeta.json

include(../../Common/BuildInfo.pri)
