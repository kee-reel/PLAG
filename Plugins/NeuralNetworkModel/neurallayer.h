#ifndef NEURALLAYER_H
#define NEURALLAYER_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include "ineuralnetworkmodel.h"

class NeuralLayer
{
public:
    NeuralLayer(NeuralLayer *PrevLayer,
                INeuralNetworkModel::NetworkParams &NetworkParams,
                INeuralNetworkModel::LayerParams &Params);
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

    INeuralNetworkModel::LayerParams params;
    inline float ActivationFunc(float x) {return 1 / (1 + expf(params.FuncIndent * -x));}
    inline float ActivationFuncDerivative(float x) {return params.FuncIndent * (1 - x) * (x);}
};

class InputNeuralLayer : public NeuralLayer
{
public:
    InputNeuralLayer(INeuralNetworkModel::NetworkParams &NetworkParams, INeuralNetworkModel::LayerParams &Params);

public slots:
    void Forward(QVector<float> &inputSignals) override;
    void Back(QVector<float> &nextLayerDelta) override;
};

class OutputNeuralLayer : public NeuralLayer
{
public:
    OutputNeuralLayer(NeuralLayer *PrevLayer,
                      INeuralNetworkModel::NetworkParams &networkParams,
                      INeuralNetworkModel::LayerParams &params);
    inline QVector<float> *GetOutputs() { return &outputs; }

public slots:
    void Forward(QVector<float> &inputSignals) override;
    void InitBack(QVector<float> &idealResult);

};

#endif // NEURALLAYER_H
