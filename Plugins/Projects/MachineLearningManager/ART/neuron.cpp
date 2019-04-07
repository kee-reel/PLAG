#include "neuron.h"

Neuron::Neuron(int size, float *L)
{
    inputWeights.resize(size);
    outputWeights.resize(size);
    this->L = L;

    float b = *L / (*L + size + 1);
    for(int i = 0; i < inputWeights.length(); ++i)
    {
        inputWeights[i] = b;
        outputWeights[i] = 1;
    }
    qDebug() << ">New neuron:" << endl << "B" << inputWeights << endl << "T" << outputWeights << endl;
}

Neuron::Neuron(int size, float *L, QVector<int> &input)
{
    inputWeights.resize(size);
    outputWeights.resize(size);
    this->L = L;

    int inputCount = 0;
    for(int i = 0; i < input.length(); ++i)
    {
        if(input[i]) inputCount++;
        outputWeights[i] = input[i];
    }
    float b = *L / (*L - 1 + inputCount);
    for(int i = 0; i < input.length(); ++i)
    {
        inputWeights[i] = input[i] ? b : 0;
    }
    qDebug() << ">New neuron:" << endl << "B" << inputWeights << endl << "T" << outputWeights << endl;
}

void Neuron::RecombineWeights(QVector<int> &input)
{
    int inputCount = 0;
    for(int i = 0; i < input.length(); ++i)
    {
        if(input[i]) inputCount++;
        outputWeights[i] = input[i];
    }
    float b = *L / (*L - 1 + inputCount);
    for(int i = 0; i < input.length(); ++i)
    {
        inputWeights[i] = input[i] ? b : 0;
    }
    qDebug() << ">Recombine weights:" << endl << "B" << inputWeights << endl << "T" << outputWeights << endl;
}

float Neuron::GetConvolution(QVector<int> &input)
{
    float result = 0;
    for(int i = 0; i < input.length(); ++i)
        if(input[i] && outputWeights[i])
            result += inputWeights[i];
    return result;
}
