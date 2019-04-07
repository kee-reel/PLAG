#include "machinelearningmanager.h"

MachineLearningManager::MachineLearningManager()
{
    tableName = "TaskTree";
}

MachineLearningManager::~MachineLearningManager()
{
}

IMachineLearningManager::ILearningAlgorithm *MachineLearningManager::SetupNetwork(QJsonObject networkParams)
{
    if(!networkParams.contains("Type"))
        return nullptr;

    ILearningAlgorithm *result;
    QString buf = networkParams.value("Type").toString();
    if(!buf.compare("Perceptron"))
        result = static_cast<ILearningAlgorithm *>(Perceptron::Make(networkParams));
    if(!buf.compare("ART"))
        result = static_cast<ILearningAlgorithm *>(ARTNetwork::Make(networkParams));
    if(!buf.compare("GeneticAlgorithm"))
        result = static_cast<ILearningAlgorithm *>(GeneticAlgorithm::Make(networkParams));

    return result;
}
