#ifndef NEURALLAYER_H
#define NEURALLAYER_H

#include <QVector>

class NeuralLayer
{
public:
    NeuralLayer(int neuronsValue, NeuralLayer* prevLayer);

    void Forward(QVector<float> &prevOutputs);
    void Backpropagation(NeuralLayer* prevLayer);
    inline int GetSize() {return outputs.size();}

private:
    NeuralLayer *prevLayer;
    NeuralLayer *nextLayer;
    QVector<QVector<float>> weights;
    QVector<float> inputs;
    QVector<float> outputs;

    static inline float ActivationFunc(float x) {return 1/(1+expf(-x));}
};

#endif // NEURALLAYER_H
