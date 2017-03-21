#ifndef EMPTYPLUGINMODEL_H
#define EMPTYPLUGINMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "ineuralnetworkmodel.h"
#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"
#include "neuralnetwork.h"

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
    NeuralNetwork *neuralNetwork;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IModelPlugin interface
public:
    void AddChildModel(IModelPlugin *model, MetaInfo *meta) override;
    void AddView(IViewPlugin *view, MetaInfo *meta) override;
    void AddDataManager(QObject *dataManager) override;
    bool Open(IModelPlugin *parent, QWidget *parentWidget) override;
    bool CloseFromView(IViewPlugin *view) override;
    void ChildSelfClosed(IModelPlugin *child) override;

    // INeuralNetworkModel interface
public:
    void SetupNetwork(NetworkParams params) override;
    void AddLayer(LayerType type, LayerParams params) override;

    // INeuralNetworkModel interface
public:
    bool RunTraining() override;
    void SetupTrainingSamples(QVector<TrainSample> *samples) override;
    bool RunTest() override;
    void SetupTestSamples(QVector<TrainSample> *samples) override;
};

#endif // EMPTYPLUGINMODEL_H
