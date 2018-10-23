#ifndef NEURON_H
#define NEURON_H

#include <QVector>
#include <QDebug>

class Neuron
{
public:
    QVector<int> outputWeights;

    Neuron(int size, float *L);
    Neuron(int size, float *L, QVector<int> &input);
    void RecombineWeights(QVector<int> &input);
    float GetConvolution(QVector<int> &input);

private:
    float *L;
    QVector<float> inputWeights;
};

#endif // NEURON_H
