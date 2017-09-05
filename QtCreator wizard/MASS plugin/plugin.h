%{Cpp:LicenseTemplate}\
#ifndef %{GUARD}
#define %{GUARD}

#include <QObject>
#include <QDebug>
#include <QString>
@if '%{PluginType}' === 'View'
/*
namespace Ui {
    class Form;
}
*/
@endif

#include "%{IFileName}"

//! \addtogroup %{CN}_imp
//! \{
class %{CN} : public 
@if '%{PluginType}' === 'View'
    QWidget,
@else
    QObject,
@endif
    %{InterfaceName}
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
@if '%{PluginType}' === 'RootModel'
        IRootModel
        IModelPlugin
@elsif '%{PluginType}' === 'Model'
        IModelPlugin
@elsif '%{PluginType}' === 'View'
        IViewPlugin
@elsif '%{PluginType}' === 'DataManager'
        IDataManagerPlugin
@elsif '%{PluginType}' === 'DataSource'
        IDataSourcePlugin
@endif
        %{InterfaceName}
    )

public:
@if '%{PluginType}' === 'View'
    explicit %{CN}(QWidget *parent = 0);
@else
    %{CN}();
@endif
    ~%{CN}();

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

signals:
    void OnClose(PluginInfo*);
    void OnClose();

@if '%{PluginType}' === 'RootModel'
    // IRootModelPlugin interface
public:
    void AddPlugin(QObject *instance, QJsonObject *meta) override;
    void Open(QWidget *parentWidget) override;

@elsif '%{PluginType}' === 'Model'
    // IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    void Close() override;

@elsif '%{PluginType}' === 'View'
    // IViewPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    bool Close() override;

signals:
    void OnOpen(QWidget *);

@elsif '%{PluginType}' === 'DataManager'

@elsif '%{PluginType}' === 'DataSource'
    // IDataSourcePlugin interface
public:
    void Setup() override;

@endif

private:
    PluginInfo *pluginInfo;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;

private:
    // Write your internal methods here
@if '%{PluginType}' === 'View'
//    Ui::Form *ui;
@endif
};
//! \}
#endif // %{GUARD}
