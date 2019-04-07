#include "recognitionlayer.h"

RecognitionLayer::RecognitionLayer(int size, NetworkParams *params)
{
    this->params = params;
    Neuron *newNeuron = new Neuron(size, &params->L);
    neurons.append(newNeuron);
}

void RecognitionLayer::Input(QVector<int> &input)
{
    if(neurons.count() == 1)
    {
        CreateNewNeuron(input);
        return;
    }

    int index = -1;
    float max = -1;
    float buf;
    qDebug() << "Convolutions";
    for(int i = 0; i < neurons.length(); ++i)
    {
        buf = neurons[i]->GetConvolution(input);
        qDebug() << "Neuron" << i << buf;
        if(buf > max)
        {
            max = buf;
            index = i;
        }
    }
    qDebug() << "Winner:" << index << "with" << max;
    if(index == 0)
    {
        CreateNewNeuron(input);
        return;
    }
    activeNeuron = neurons[index];
    comparingLayer->Response(activeNeuron->outputWeights);
}

void RecognitionLayer::CreateNewNeuron(QVector<int> &input)
{
    Neuron *newNeuron = new Neuron(input.length(), &params->L, input);
    neurons.append(newNeuron);
}

void RecognitionLayer::RefreshActiveNeuron(QVector<int> &input)
{
    activeNeuron->RecombineWeights(input);
}
