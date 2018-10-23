#ifndef NEURALNETWORKMODEL_H
#define NEURALNETWORKMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QJsonObject>

#include "../../DataManagers/ExtendableDataManager/iextendabledatamanager.h"
#include "ineuralnetworkmodel.h"

#include "Perceptron/perceptronnetwork.h"
#include "ART/artnetwork.h"
#include "GeneticAlgorithm/geneticalgorithm.h"

//! \addtogroup NeuralNetworkModel_imp
//! \{
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
    IExtendableDataManager* dataManager;

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

    // IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    void Close() override;

    // INeuralNetworkModel interface
public:
    INeuralNetwork *SetupNetwork(QJsonObject networkParams) override;
};
//! \}
#endif
