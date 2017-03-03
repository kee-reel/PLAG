#ifndef MAINMENUMODULE_H
#define MAINMENUMODULE_H

#include <QObject>
#include <QDebug>
#include <QApplication>

#include "imainmenumodule.h"
#include "../../System/ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"

class MainMenuModelPlugin : public QObject, IMainMenuPluginModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin IRootModelPlugin IMainMenuPluginModel)

public:
    MainMenuModelPlugin();
    ~MainMenuModelPlugin();

    void OnAllSetup() override;
    QString GetLastError() override;

    void AddDataSource(IDataSourcePlugin *view, QObject *instance, MetaInfo *meta) override;
    void AddDataManager(IDataManagerPlugin *view, QObject *instance, MetaInfo *meta) override;
    void AddView(IDataSourcePlugin *view, QObject *instance, MetaInfo *meta) override;
    void AddModel(IDataManagerPlugin *view, QObject *instance, MetaInfo *meta) override;

    void AddDataManager(QObject *dataManager) override;
    void AddChildModel(IModelPlugin *model, MetaInfo *meta) override;
    void AddView(IViewPlugin *, MetaInfo *) override;

    bool Open(IModelPlugin *myParent, QWidget *parentWidget, int id) override;
    bool Close() override;
    void ChildSelfClosed(int id) override;

    QList<MetaInfo *> GetChildPlugins() override;
    void RunPlugin(int pluginId) override;

private:

    QWidget *myParentWidget;
    int myModelId;
    int activeViewId;
    int activeModelId;

};

#endif // MAINMENUMODULE_H
