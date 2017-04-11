#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(Perceptron::NetworkParams params) : QObject()
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

void NeuralNetwork::AddLayer(Perceptron::LayerType type, Perceptron::LayerParams params)
{
    switch (type) {
    case Perceptron::Input:{
        if(inputLayer) delete inputLayer;
        inputLayer = new InputNeuralLayer(networkParams, params);
        }
        break;

    case Perceptron::Hidden:{
        NeuralLayer *connectedLayer = layers.count() ? layers.last() : inputLayer;
        NeuralLayer *newLayer = new NeuralLayer(connectedLayer, networkParams, params);
        layers.append(newLayer);
        }
        break;

    case Perceptron::Output:{
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

float NeuralNetwork::RunTraining()
{   
    resultError = 0;
    for(int j = 0; j < trainingSamples->length(); ++j)
        resultError += RunTrainSet((*trainingSamples)[j]);
    resultError /= trainingSamples->length();
//    float errBuf = 0;
//    trainErrorVector->clear();
//    int epoch;
//    for(epoch = 0; epoch < networkParams.maxEpoch; ++epoch)
//    {
//        for(int j = 0; j < trainingSamples->length(); ++j)
//            resultError += RunTrainSet((*trainingSamples)[j]);
//        resultError /= trainingSamples->length();
//        trainErrorVector->append(resultError);
//        qDebug() << "Epoch" << epoch;
//        qDebug() << "Current error" << resultError << "[" << (resultError - errBuf) << "]";
//        if(resultError < networkParams.trainErrorThreshold)
//        {
//            qDebug() << "Algorithm succeded";
//            return true;
//        }
//        errBuf = resultError;
//        resultError = 0;
//    }
    return resultError;
}

float NeuralNetwork::RunTest()
{
    resultError = 0;
    for(int j = 0; j < testSamples->length(); ++j)
        resultError += RunTestSet((*testSamples)[j]);
    resultError /= testSamples->length();
    return resultError;
}

float NeuralNetwork::RunTrainSet(INeuralNetworkModel::TrainSample &trainSet)
{
    inputLayer->Forward(trainSet.first);
    QString result = "";
    resultError = 0;
    for(int i = 0; i < outputLayer->outputs.length(); ++i)
    {
        result.append(QString::number(trainSet.second[i]) + "~" + QString::number(outputLayer->outputs[i]) + ", ");
        resultError += (trainSet.second[i] - outputLayer->outputs[i]) * (trainSet.second[i] - outputLayer->outputs[i]);
    }
    outputLayer->InitBack(trainSet.second);
    return resultError;
}

float NeuralNetwork::RunTestSet(INeuralNetworkModel::TrainSample &testSet)
{
    inputLayer->Forward(testSet.first);
    QString result = "";
    resultError = 0;
    for(int i = 0; i < outputLayer->outputs.length(); ++i)
    {
        result.append(QString::number(testSet.second[i]) + "~" + QString::number(outputLayer->outputs[i]) + ", ");
        resultError += (testSet.second[i] - outputLayer->outputs[i]) * (testSet.second[i] - outputLayer->outputs[i]);
    }
    return resultError;
}
