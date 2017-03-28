#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(INeuralNetworkModel::NetworkParams params) : QObject()
{
    inputLayer = NULL;
    outputLayer = NULL;
    maxEpoch = params.maxEpoch;
    resultError = 0;
    resultErrorThreshold = params.resultErrorThreshold;
}

NeuralNetwork::~NeuralNetwork()
{
    if(inputLayer) delete inputLayer;
    if(outputLayer) delete outputLayer;
    for(int i = 0; i < layers.length(); ++i)
        delete layers[i];
}

void NeuralNetwork::AddInputLayer(INeuralNetworkModel::LayerParams params)
{
    if(inputLayer) delete inputLayer;
    inputLayer = new InputNeuralLayer(params.size, 0);
}

void NeuralNetwork::AddHiddenLayer(INeuralNetworkModel::LayerParams params)
{
    NeuralLayer *connectedLayer = layers.count() ? layers.last() : inputLayer;
    NeuralLayer *newLayer = new NeuralLayer(params.size, connectedLayer, params.LearnSpeed, params.Moment, params.FuncIndent, params.Bias);
    layers.append(newLayer);
}

void NeuralNetwork::AddOutputLayer(INeuralNetworkModel::LayerParams params)
{
    NeuralLayer *connectedLayer = layers.count() ? layers.last() : inputLayer;
    if(outputLayer) delete outputLayer;
    NeuralLayer *connectedLayer = layers.count() ? layers.last() : inputLayer;
    outputLayer = new OutputNeuralLayer(params.size, connectedLayer, params.LearnSpeed, params.Moment, params.FuncIndent, params.Bias);
}

bool NeuralNetwork::RunTraining()
{   
    for(int epoch = 0; epoch < maxEpoch; ++epoch)
    {
        qDebug() << "Epoch" << epoch;

        for(int j = 0; j < trainingSamples->length(); ++j)
            resultError += RunTrainSet((*trainingSamples)[j]);

        resultError /= trainingSamples->length();
        qDebug() << "Current error" << resultError;
        if(resultError < resultErrorThreshold)
        {
            qDebug() << "Algorithm succeded";
            return true;
        }
        resultError = 0;
    }
    qDebug() << "Algorithm reached max epoch";
    return false;
}

float NeuralNetwork::RunTrainSet(INeuralNetworkModel::TrainSample &trainSet)
{
    inputLayer->Forward(trainSet.first);
    QString result = "";
    for(int i = 0; i < trainSet.first.length(); ++i)
        result.append(QString::number(trainSet.first[i]) + ", ");
    result.append(" -> ");
    for(int i = 0; i < outputLayer->outputs.length(); ++i)
        result.append(QString::number(trainSet.second[i]) + "~" + QString::number(outputLayer->outputs[i]) + ", ");
    qDebug() << result;
    float buf = outputLayer->InitBackpropagation(trainSet.second);
    return buf * buf;
}

bool NeuralNetwork::RunTest()
{
    resultError = 0;
    for(int j = 0; j < testSamples->length(); ++j)
    {
        resultError += RunTrainSet((*testSamples)[j]);
    }
    resultError /= testSamples->length();
    qDebug() << resultError;
    return resultError < resultErrorThreshold;
}

float NeuralNetwork::RunTestSet(INeuralNetworkModel::TrainSample &testSet)
{
    inputLayer->Forward(testSet.first);
    QString result = "";
    for(int i = 0; i < testSet.first.length(); ++i)
        result.append(QString::number(testSet.first[i]) + ", ");
    result.append(" -> ");
    for(int i = 0; i < outputLayer->outputs.length(); ++i)
    {
        result.append(QString::number(testSet.second[i]) + "~" + QString::number(outputLayer->outputs[i]) + ", ");
        resultError += (testSet.second[i] - outputLayer->outputs[i]) * (testSet.second[i] - outputLayer->outputs[i]);
    }
    qDebug() << result;
}
