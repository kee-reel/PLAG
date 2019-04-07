#ifndef NEURALLAYER_H
#define NEURALLAYER_H

#include <QtCore>
#include <QVector>
#include <QDebug>

#include "parameters.h"

class NeuralLayer
{
protected:
    typedef Parameters::Perceptron::NetworkParams NetworkParams;
    typedef Parameters::Perceptron::LayerParams LayerParams;
    typedef Parameters::Perceptron::LayerType LayerType;
public:
    NeuralLayer(NeuralLayer *PrevLayer,
                NetworkParams &NetworkParams,
                LayerParams &Params);
    inline int LayerSize() {return outputs.size();}

public slots:
    virtual void Forward(QVector<float> &prevOutputs);
    virtual void Back(QVector<float> &nextLayerDelta);

public:
    NeuralLayer *prevLayer;
    NeuralLayer *nextLayer;
    QVector<QVector<float>> inputWeights;
    QVector<QVector<float>> weightsDelta;
    QVector<QVector<float>> *outputWeights;
    QVector<float> inputs;
    QVector<float> outputs;
    QVector<float> layerDelta;

    LayerParams params;
    inline float ActivationFunc(float x) {return 1 / (1 + expf(params.FuncIndent * -x));}
    inline float ActivationFuncDerivative(float x) {return params.FuncIndent * (1 - x) * (x);}
};

class InputNeuralLayer : public NeuralLayer
{
public:
    InputNeuralLayer(NetworkParams &NetworkParams, LayerParams &Params);

public slots:
    void Forward(QVector<float> &inputSignals) override;
    void Back(QVector<float> &nextLayerDelta) override;
};

class OutputNeuralLayer : public NeuralLayer
{
public:
    OutputNeuralLayer(NeuralLayer *PrevLayer,
                      NetworkParams &networkParams,
                      LayerParams &params);
    inline QVector<float> *GetOutputs() { return &outputs; }

public slots:
    void Forward(QVector<float> &inputSignals) override;
    void InitBack(QVector<float> &idealResult);

};

#endif // NEURALLAYER_H
