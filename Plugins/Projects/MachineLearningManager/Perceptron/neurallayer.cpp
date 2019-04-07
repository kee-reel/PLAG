#include "neurallayer.h"

NeuralLayer::NeuralLayer(NeuralLayer *PrevLayer, NetworkParams &NetworkParams, LayerParams &Params)
{
    prevLayer = PrevLayer;
    nextLayer = NULL;
    params = Params;
    outputs.resize(params.size);
    layerDelta.resize(params.size);
    if(!PrevLayer)
        return;

    prevLayer->nextLayer = this;
    prevLayer->outputWeights = &inputWeights;
    inputWeights.resize(LayerSize());
    weightsDelta.resize(LayerSize());

    float range = NetworkParams.maxWeight - NetworkParams.minWeight;
    for(int i = 0; i < LayerSize(); ++i)
    {
        inputWeights[i].resize(prevLayer->LayerSize());
        weightsDelta[i].resize(prevLayer->LayerSize());
        for(int j = 0; j < inputWeights[i].size(); ++j)
        {
            inputWeights[i][j] = NetworkParams.minWeight + (qrand()/double(RAND_MAX))*range;
            weightsDelta[i][j] = 0;
        }
    }
}

void NeuralLayer::Forward(QVector<float> &prevOutputs)
{
    for(int myLayerNeuron = 0; myLayerNeuron < LayerSize(); ++myLayerNeuron)
    {
        outputs[myLayerNeuron] = 0;
        for(int prevLayerNeuron = 0; prevLayerNeuron < prevLayer->LayerSize(); ++prevLayerNeuron)
            outputs[myLayerNeuron] += prevOutputs[prevLayerNeuron] * inputWeights[myLayerNeuron][prevLayerNeuron];
        outputs[myLayerNeuron] = ActivationFunc(outputs[myLayerNeuron]);
    }
    qDebug() << "outputs" << outputs;
    if(nextLayer)
        nextLayer->Forward(outputs);
}

void NeuralLayer::Back(QVector<float> &nextLayerDelta)
{
    float delta;
    for(int i = 0; i < LayerSize(); ++i)
    {
        layerDelta[i] = ActivationFuncDerivative(outputs[i]);
        for(int j = 0; j < nextLayer->LayerSize(); ++j)
        {
            layerDelta[i] += nextLayer->inputWeights.at(j).at(i) * nextLayerDelta[j];
            delta = nextLayer->params.LearnSpeed * nextLayerDelta[j] * outputs[i]
                    + nextLayer->params.Moment * nextLayer->weightsDelta[j][i];
            nextLayer->inputWeights[j][i] -= delta;
            nextLayer->weightsDelta[j][i] = delta;
        }
    }
    if(prevLayer)
        prevLayer->Back(layerDelta);
}

InputNeuralLayer::InputNeuralLayer(NetworkParams &NetworkParams, LayerParams &Params)
    : NeuralLayer(NULL, NetworkParams, Params)
{

}

void InputNeuralLayer::Forward(QVector<float> &inputSignals)
{
    for(int i = 0; i < LayerSize(); ++i)
        outputs[i] = inputSignals[i] + params.Bias;
    nextLayer->Forward(outputs);
}

void InputNeuralLayer::Back(QVector<float> &nextLayerDelta)
{
    float delta;
    for(int i = 0; i < LayerSize(); ++i)
    {
        for(int j = 0; j < nextLayer->LayerSize(); ++j)
        {
            delta = nextLayer->params.LearnSpeed * nextLayerDelta[j] * outputs[i]
                    + nextLayer->params.Moment * nextLayer->weightsDelta[j][i];
            nextLayer->inputWeights[j][i] -= delta;
            nextLayer->weightsDelta[j][i] = delta;
        }
    }
}

OutputNeuralLayer::OutputNeuralLayer(NeuralLayer *PrevLayer, NetworkParams &networkParams, LayerParams &params)
    : NeuralLayer(PrevLayer, networkParams, params)
{

}

void OutputNeuralLayer::Forward(QVector<float> &inputSignals)
{
    NeuralLayer::Forward(inputSignals);
}

void OutputNeuralLayer::InitBack(QVector<float> &idealResult)
{
    float buf;
    for(int i = 0; i < idealResult.size(); ++i)
    {
        buf = outputs[i] - idealResult[i];
        layerDelta[i] = buf * ActivationFuncDerivative(outputs[i]);
    }
    prevLayer->Back(layerDelta);
}
