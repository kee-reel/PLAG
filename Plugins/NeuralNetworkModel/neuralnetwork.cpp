#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(INeuralNetworkModel::NetworkParams params) : QObject()
{
    inputLayer = NULL;
    outputLayer = NULL;
    networkParams = params;
    resultError = 0;
}

NeuralNetwork::~NeuralNetwork()
{
    if(inputLayer) delete inputLayer;
    if(outputLayer) delete outputLayer;
    for(int i = 0; i < layers.length(); ++i)
        delete layers[i];
}

void NeuralNetwork::AddLayer(INeuralNetworkModel::LayerType type, INeuralNetworkModel::LayerParams params)
{
    switch (type) {
    case INeuralNetworkModel::Input:{
        if(inputLayer) delete inputLayer;
        inputLayer = new InputNeuralLayer(networkParams, params);
        }
        break;

    case INeuralNetworkModel::Hidden:{
        NeuralLayer *connectedLayer = layers.count() ? layers.last() : inputLayer;
        NeuralLayer *newLayer = new NeuralLayer(connectedLayer, networkParams, params);
        layers.append(newLayer);
        }
        break;

    case INeuralNetworkModel::Output:{
        if(outputLayer) delete outputLayer;
        NeuralLayer *connectedLayer = layers.count() ? layers.last() : inputLayer;
        outputLayer = new OutputNeuralLayer(connectedLayer, networkParams, params);
        }
        break;
    }
}

void NeuralNetwork::ResetLayers()
{
    if(inputLayer)
    {
        delete inputLayer;
        inputLayer = NULL;
    }
    if(outputLayer)
    {
        delete outputLayer;
        outputLayer = NULL;
    }

    for(int i = 0; i < layers.length(); ++i)
        delete layers[i];
    layers.clear();
}

bool NeuralNetwork::RunTraining(QVector<double> *errorVector)
{   
    float errBuf = 0;
    errorVector->clear();
    int epoch;
    for(epoch = 0; epoch < networkParams.maxEpoch; ++epoch)
    {
        for(int j = 0; j < trainingSamples->length(); ++j)
            resultError += RunTrainSet((*trainingSamples)[j]);
        resultError /= trainingSamples->length();
        errorVector->append(resultError);
        qDebug() << "Epoch" << epoch;
        qDebug() << "Current error" << resultError << "[" << (resultError - errBuf) << "]";
        if(resultError < networkParams.trainErrorThreshold)
        {
            qDebug() << "Algorithm succeded";
            return true;
        }
        errBuf = resultError;
        resultError = 0;
    }
    return false;
}

bool NeuralNetwork::ResumeTraining(QVector<double> *errorVector)
{
    float errBuf = 0;
    int epoch;
    for(epoch = 0; epoch < networkParams.maxEpoch; ++epoch)
    {
        for(int j = 0; j < trainingSamples->length(); ++j)
            resultError += RunTrainSet((*trainingSamples)[j]);
        resultError /= trainingSamples->length();
        errorVector->append(resultError);
        qDebug() << "Epoch" << epoch;
        qDebug() << "Current error" << resultError << "[" << (resultError - errBuf) << "]";
        if(resultError < networkParams.trainErrorThreshold)
        {
            qDebug() << "Algorithm succeded";
            break;
        }
        errBuf = resultError;
        resultError = 0;
    }
    return false;
}

float NeuralNetwork::RunTrainSet(INeuralNetworkModel::TrainSample &trainSet)
{
    inputLayer->Forward(trainSet.first);
    QString result = "";
    for(int i = 0; i < outputLayer->outputs.length(); ++i)
        result.append(QString::number(trainSet.second[i]) + "~" + QString::number(outputLayer->outputs[i]) + ", ");
    qDebug() << result;
    float buf = outputLayer->InitBack(trainSet.second);
    return buf;
}

bool NeuralNetwork::RunTest()
{
    resultError = 0;
    for(int j = 0; j < testSamples->length(); ++j)
    {
        resultError += RunTestSet((*testSamples)[j]);
    }
    resultError /= testSamples->length();
    qDebug() << resultError;
    return resultError < networkParams.testErrorThreshold;
}

float NeuralNetwork::RunTestSet(INeuralNetworkModel::TrainSample &testSet)
{
    inputLayer->Forward(testSet.first);
    QString result = "";
    for(int i = 0; i < outputLayer->outputs.length(); ++i)
    {
        result.append(QString::number(testSet.second[i]) + "~" + QString::number(outputLayer->outputs[i]) + ", ");
        resultError += (testSet.second[i] - outputLayer->outputs[i]) * (testSet.second[i] - outputLayer->outputs[i]);
    }
    qDebug() << result;
    return resultError;
}
