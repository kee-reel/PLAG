#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(int inputs) : QObject()
{
    inputLayer = new InputNeuralLayer(inputs);
    //hiddenLayers.append(new NeuralLayer(2*inputs, inputLayer));
    outputLayer = new OutputNeuralLayer(1, inputLayer);//hiddenLayers.last());
    maxEpoch = 100;
    resultError = 0;
    resultErrorThreshold = 0.01;

    TrainingPair buf;
    buf.inputs = {1, 1};
    buf.outputs = {1};
    trainingSamples.append(buf);
    buf.inputs = {0, 0};
    buf.outputs = {0};
    trainingSamples.append(buf);
    buf.inputs = {0, 1};
    buf.outputs = {1};
    trainingSamples.append(buf);
    buf.inputs = {1, 0};
    buf.outputs = {1};
    trainingSamples.append(buf);

    RunEpoch();
}

void NeuralNetwork::RunEpoch()
{
    for(int epoch = 0; epoch < maxEpoch; ++epoch)
    {
        qDebug() << "Epoch" << epoch;

        for(int j = 0; j < trainingSamples.length(); ++j)
            RunTrainSet(j);

        resultError /= trainingSamples.length();
        qDebug() << "Current error" << resultError;
        if(resultError < resultErrorThreshold)
        {
            qDebug() << "Algorithm succeded";
            return;
        }
        resultError = 0;
    }
    qDebug() << "Algorithm reached max epoch";
}

void NeuralNetwork::RunTrainSet(int trainSet)
{
    for(int i = 0; i < trainingSamples[trainSet].inputs.length(); ++i)
        qDebug() << trainingSamples[trainSet].inputs[i];
    inputLayer->Forward(trainingSamples[trainSet].inputs);
    float buf = outputLayer->InitBackpropagation(trainingSamples[trainSet].outputs);
    resultError += buf * buf;
}
