#ifndef NEURALNETWORKMODEL_H
#define NEURALNETWORKMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QJsonObject>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/iextendabledatamanager.h"
#include "../../Interfaces/ineuralnetworkmodel.h"

#include "Perceptron/perceptronnetwork.h"
#include "ART/artnetwork.h"
#include "GeneticAlgorithm/geneticalgorithm.h"

//! \addtogroup NeuralNetworkModel_imp
//! \{
class NeuralNetworkModel : public PluginBase, INeuralNetworkModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin INeuralNetworkModel)

public:
    NeuralNetworkModel();
    virtual ~NeuralNetworkModel() override;

private:
    // Unique part
    QString tableName;
    IExtendableDataManager* dataManager;

    // INeuralNetworkModel interface
public:
    INeuralNetwork *SetupNetwork(QJsonObject networkParams) override;
};
//! \}
#endif
