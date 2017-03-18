#ifndef EMPTYPLUGINMODEL_H
#define EMPTYPLUGINMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "ineuralnetworkmodel.h"
#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"

class NeuralNetworkModel : public QObject, INeuralNetworkModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin INeuralNetworkModel)

public:
    NeuralNetworkModel();
    ~NeuralNetworkModel();

private:
    // Native part
    IModelPlugin *myParent;
    QWidget *myParentWidget;
    int myModelId;
    int activeViewId;
    int activeModelId;

    template <class T>
    struct PluginInfo
    {
        T *plugin;
        MetaInfo *meta;
    };

    QList< PluginInfo<IModelPlugin> > childModelPlugins;
    QList< PluginInfo<IViewPlugin> > viewPlugins;

    // Unique part
    QString tableName;
    IExtendableDataBaseManagerPlugin* dataManager;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IModelPlugin interface
public:
    void AddChildModel(IModelPlugin *model, MetaInfo *meta) override;
    void AddView(IViewPlugin *view, MetaInfo *meta) override;
    void AddDataManager(QObject *dataManager) override;
    bool Open(IModelPlugin *parent, QWidget *parentWidget, int id) override;
    bool Close() override;
    void ChildSelfClosed(int id) override;

    // INeuralNetworkModel interface
public:
    void TestFunc() override;
};

#endif // EMPTYPLUGINMODEL_H