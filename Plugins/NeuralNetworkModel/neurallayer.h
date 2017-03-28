#ifndef NEURALLAYER_H
#define NEURALLAYER_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QMatrix>

class NeuralLayer
{
public:
    NeuralLayer(int NeuronsValue,
                NeuralLayer *PrevLayer,
                float LearnSpeed = 0.7,
                float Moment = 0.3,
                float FuncIndent = 10,
                float Bias = 0);
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

    float learnSpeed;
    float moment;
    float funcIndent;
    float bias;
    inline float ActivationFunc(float x) {return 1 / (1 + expf(funcIndent*-x));}
    inline float ActivationFuncDerivative(float x) {return funcIndent * (1 - x) * (x);}
};

class InputNeuralLayer : public NeuralLayer
{
public:
    InputNeuralLayer(int NeuronsValue,
                     float Bias = 0);

public slots:
    void Forward(QVector<float> &inputSignals) override;
    void Back(QVector<float> &nextLayerDelta) override;
};

class OutputNeuralLayer : public NeuralLayer
{
public:
    OutputNeuralLayer(int NeuronsValue,
                      NeuralLayer *PrevLayer,
                      float LearnSpeed = 0.7,
                      float Moment = 0.3,
                      float Bias = -0.5,
                      float FuncIndent = 2);
    inline QVector<float> *GetOutputs() { return &outputs; }

public slots:
    void Forward(QVector<float> &inputSignals) override;
    float InitBack(QVector<float> &idealResult);

};

#endif // NEURALLAYER_H
