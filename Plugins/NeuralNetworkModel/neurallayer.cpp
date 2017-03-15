#include "neurallayer.h"

NeuralLayer::NeuralLayer(int neuronsValue, NeuralLayer* prevLayer)
{
    inputs.reserve(neuronsValue);
    outputs.resize(neuronsValue);
    weights.resize(outputs.size());
    for(int i = 0; i < weights.size(); ++i)
        weights[i].resize(prevLayer->GetSize());
    this->prevLayer = prevLayer;
}

void NeuralLayer::Forward(QVector<float> &prevOutputs)
{
    for(int myLayerNeuron = 0; myLayerNeuron < weights.size(); ++myLayerNeuron)
    {
        for(int prevLayerNeuron = 0; prevLayerNeuron < weights[myLayerNeuron].size(); ++prevLayerNeuron)
            inputs[myLayerNeuron] = prevOutputs[prevLayerNeuron] * weights[myLayerNeuron][prevLayerNeuron];
        outputs[myLayerNeuron] = ActivationFunc(inputs[j]);
    }
}

void NeuralLayer::Backpropagation(NeuralLayer *prevLayer)
{

}
