#ifndef NEURALLAYER_H
#define NEURALLAYER_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QMatrix>

class NeuralLayer : public QObject
{
    Q_OBJECT
public:
    explicit NeuralLayer(int NeuronsValue, NeuralLayer *PrevLayer);
    inline int LayerSize() {return outputs.size();}

public slots:
    virtual void Forward(QVector<float> &prevOutputs);
    virtual void Back(QVector<float> &nextLayerDelta);

protected :
    NeuralLayer *prevLayer;
    NeuralLayer *nextLayer;
    QVector<QVector<float>> inputWeights;
    QVector<QVector<float>> weightsDelta;
    QVector<QVector<float>> *outputWeights;
    QVector<float> inputs;
    QVector<float> outputs;
    QVector<float> currentLayerDelta;
    static inline float ActivationFunc(float x) {return 1/(1+expf(0.6*-x));}
};

class InputNeuralLayer : public NeuralLayer
{
    Q_OBJECT
public:
    InputNeuralLayer(int NeuronsValue);

public slots:
    void Forward(QVector<float> &inputSignals) override;
    void Back(QVector<float> &nextLayerDelta) override;
};

class OutputNeuralLayer : public NeuralLayer
{
    Q_OBJECT
public:
    OutputNeuralLayer(int NeuronsValue, NeuralLayer *PrevLayer);
    inline QVector<float> GetOutputs() { return outputs; }

public slots:
    void Forward(QVector<float> &inputSignals) override;
    float InitBackpropagation(QVector<float> &idealResult);
};

#endif // NEURALLAYER_H
