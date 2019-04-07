#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QJsonObject>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/iextendabledatamanager.h"
#include "../../Interfaces/imachinelearningmanager.h"

#include "Perceptron/perceptron.h"
#include "ART/artnetwork.h"
#include "GeneticAlgorithm/geneticalgorithm.h"

//! \addtogroup MachineLearningManager_imp
//! \{
class MachineLearningManager : public PluginBase, IMachineLearningManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin IMachineLearningManager)

public:
    MachineLearningManager();
    virtual ~MachineLearningManager() override;

private:
    // Unique part
    QString tableName;
    IExtendableDataManager* dataManager;

    // INeuralNetwork interface
public:
    ILearningAlgorithm *SetupNetwork(QJsonObject networkParams) override;
};
//! \}
#endif
