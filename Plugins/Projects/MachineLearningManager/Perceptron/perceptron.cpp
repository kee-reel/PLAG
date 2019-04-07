#include "perceptron.h"

Perceptron::Perceptron(NetworkParams params) : QObject()
{
    inputLayer = NULL;
    outputLayer = NULL;
    networkParams = params;
    resultError = 0;
}

Perceptron *Perceptron::Make(QJsonObject &paramsObj)
{
    Perceptron *network;
    NetworkParams params;
    params.trainErrorThreshold  = paramsObj.value("trainErrorThreshold").toDouble();
    params.testErrorThreshold   = paramsObj.value("testErrorThreshold").toDouble();
    params.minWeight            = paramsObj.value("minWeight").toDouble();
    params.maxWeight            = paramsObj.value("maxWeight").toDouble();
    params.maxEpoch             = paramsObj.value("maxEpoch").toInt();
    network = new Perceptron(params);
    return network;
}

Perceptron::~Perceptron()
{
    if(inputLayer) delete inputLayer;
    if(outputLayer) delete outputLayer;
    for(int i = 0; i < layers.length(); ++i)
        delete layers[i];
}

void Perceptron::ResetLayers()
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

float Perceptron::RunTrainSet()
{   
    resultError = 0;
    for(int j = 0; j < trainingSamples->length(); ++j)
        resultError += RunTrainSet((*trainingSamples)[j]);
    resultError /= trainingSamples->length();
    return resultError;
}

QVector<QVariant> Perceptron::RunTrainingAndGetResult()
{
    float errBuf = 0;
    int epoch;
    QVector<QVariant> result;
    for(epoch = 0; epoch < networkParams.maxEpoch; ++epoch)
    {
        resultError = 0;
        for(int j = 0; j < trainingSamples->length(); ++j)
            resultError += RunTrainSet((*trainingSamples)[j]);
        resultError /= trainingSamples->length();
        qDebug() << "Epoch" << epoch;
        qDebug() << "Current error" << resultError << "[" << (resultError - errBuf) << "]";
        if(resultError < networkParams.trainErrorThreshold)
        {
            qDebug() << "Algorithm succeded";
            break;
        }
        errBuf = resultError;
    }
    result.append(resultError);
    return result;
}

float Perceptron::RunTestSet()
{
    resultError = 0;
    for(int j = 0; j < testSamples->length(); ++j)
        resultError += RunTestSet((*testSamples)[j]);
    resultError /= testSamples->length();
    return resultError;
}

float Perceptron::RunTrainSet(InputSampleF &trainSet)
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

float Perceptron::RunTestSet(InputSampleF &testSet)
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

void Perceptron::SetupSamplesF(QJsonObject parameters, QVector<InputSampleF> *samples)
{
    QString typeStr = parameters.value("Type").toString();
    if(typeStr == "")
        return;
    else if(!typeStr.compare("Train"))
        trainingSamples = samples;
    else if(!typeStr.compare("Test"))
        testSamples = samples;
}

void Perceptron::SetupSamplesI(QJsonObject parameters, QVector<InputSampleI> *samples)
{
    qDebug() << "This type of data is not digestable by Perceptron :c";
}

bool Perceptron::SetNetworkParams(QJsonObject params)
{
    networkParams.trainErrorThreshold  = params.value("trainErrorThreshold").toDouble();
    networkParams.testErrorThreshold   = params.value("testErrorThreshold").toDouble();
    networkParams.minWeight            = params.value("minWeight").toDouble();
    networkParams.maxWeight            = params.value("maxWeight").toDouble();
    networkParams.maxEpoch             = params.value("maxEpoch").toInt();
}

bool Perceptron::AddLayer(QJsonObject layerParams)
{
    if(!layerParams.contains("Type"))
        return false;

    LayerType type;
    QString typeStr = layerParams.value("Type").toString();
    if(!typeStr.compare("Input"))
        type = LayerType::Input;
    else if(!typeStr.compare("Hidden"))
        type = LayerType::Hidden;
   else if(!typeStr.compare("Output"))
        type = LayerType::Output;
    else
        return false;

    LayerParams params;
    params.Bias         = layerParams.value("Bias").toDouble();
    params.FuncIndent   = layerParams.value("FuncIndent").toDouble();
    params.LearnSpeed   = layerParams.value("LearnSpeed").toDouble();
    params.Moment       = layerParams.value("Moment").toDouble();
    params.size         = layerParams.value("size").toDouble();

    switch (type) {
        case LayerType::Input:{
            if(inputLayer) delete inputLayer;
            inputLayer = new InputNeuralLayer(networkParams, params);
            }
            break;

        case LayerType::Hidden:{
            NeuralLayer *connectedLayer = layers.count() ? layers.last() : inputLayer;
            NeuralLayer *newLayer = new NeuralLayer(connectedLayer, networkParams, params);
            layers.append(newLayer);
            }
            break;

        case LayerType::Output:{
            if(outputLayer) delete outputLayer;
            NeuralLayer *connectedLayer = layers.count() ? layers.last() : inputLayer;
            outputLayer = new OutputNeuralLayer(connectedLayer, networkParams, params);
            }
            break;
    }
    return true;
}
