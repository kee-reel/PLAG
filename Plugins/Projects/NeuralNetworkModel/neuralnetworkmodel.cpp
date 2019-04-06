#include "neuralnetworkmodel.h"

NeuralNetworkModel::NeuralNetworkModel()
{
    tableName = "TaskTree";
}

NeuralNetworkModel::~NeuralNetworkModel()
{
}

INeuralNetworkModel::INeuralNetwork *NeuralNetworkModel::SetupNetwork(QJsonObject networkParams)
{
    if(!networkParams.contains("Type"))
        return nullptr;

    INeuralNetwork *result;
    QString buf = networkParams.value("Type").toString();
    if(!buf.compare("Perceptron"))
        result = static_cast<INeuralNetwork *>(PerceptronNetwork::Make(networkParams));
    if(!buf.compare("ART"))
        result = static_cast<INeuralNetwork *>(ARTNetwork::Make(networkParams));
    if(!buf.compare("GeneticAlgorithm"))
        result = static_cast<INeuralNetwork *>(GeneticAlgorithm::Make(networkParams));

    return result;
}
