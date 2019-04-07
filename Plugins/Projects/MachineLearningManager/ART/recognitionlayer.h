#ifndef RECOGNITIONLAYER_H
#define RECOGNITIONLAYER_H

#include <QVector>
#include <QDebug>

#include "parameters.h"
#include "ART/comparinglayer.h"
#include "ART/neuron.h"

class ComparingLayer;
class RecognitionLayer
{
protected:
    typedef Parameters::ART::NetworkParams NetworkParams;
public:
    NetworkParams *params;
    QVector<Neuron*> neurons;
    Neuron *activeNeuron;
    ComparingLayer *comparingLayer;
    float *L;

    RecognitionLayer(int size, NetworkParams *params);
    void Input(QVector<int> &input);
    void CreateNewNeuron(QVector<int> &input);
    void RefreshActiveNeuron(QVector<int> &input);
};

#endif // RECOGNITIONLAYER_H
