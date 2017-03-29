#include "neurallayer.h"

NeuralLayer::NeuralLayer(int NeuronsValue, NeuralLayer *PrevLayer, float LearnSpeed, float Moment, float FuncIndent, float Bias)
{
    qDebug() << "NeuralLayer created";
    prevLayer = PrevLayer;
    nextLayer = NULL;
    learnSpeed = LearnSpeed;
    moment = Moment;
    funcIndent = FuncIndent;
    bias = Bias;
    outputs.resize(NeuronsValue);
    layerDelta.resize(NeuronsValue);
    if(!PrevLayer)
        return;

    prevLayer->nextLayer = this;
    prevLayer->outputWeights = &inputWeights;
    inputWeights.resize(LayerSize());
    weightsDelta.resize(LayerSize());
    for(int i = 0; i < LayerSize(); ++i)
    {
        inputWeights[i].resize(prevLayer->LayerSize());
        weightsDelta[i].resize(prevLayer->LayerSize());
        for(int j = 0; j < inputWeights[i].size(); ++j)
        {
            inputWeights[i][j] = -1 + ((float)(qrand()%2000))/1000;
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
            delta = nextLayer->learnSpeed * nextLayerDelta[j] * outputs[i]
                    + nextLayer->moment * nextLayer->weightsDelta[j][i];
            nextLayer->inputWeights[j][i] -= delta;
            nextLayer->weightsDelta[j][i] = delta;
        }
    }
    if(prevLayer)
        prevLayer->Back(layerDelta);
}

InputNeuralLayer::InputNeuralLayer(int NeuronsValue, float Bias)
    : NeuralLayer(NeuronsValue, NULL, 0, 0, 0, Bias)
{

}

void InputNeuralLayer::Forward(QVector<float> &inputSignals)
{
    for(int i = 0; i < LayerSize(); ++i)
        outputs[i] = inputSignals[i] + bias;
    nextLayer->Forward(outputs);
}

void InputNeuralLayer::Back(QVector<float> &nextLayerDelta)
{
    float delta;
    for(int i = 0; i < LayerSize(); ++i)
    {
        for(int j = 0; j < nextLayer->LayerSize(); ++j)
        {
            delta = nextLayer->learnSpeed * nextLayerDelta[j] * outputs[i]
                    + nextLayer->moment * nextLayer->weightsDelta[j][i]; // TODO: Moment
            nextLayer->inputWeights[j][i] -= delta;
            nextLayer->weightsDelta[j][i] = delta;
        }
    }
}

OutputNeuralLayer::OutputNeuralLayer(int NeuronsValue, NeuralLayer *PrevLayer, float LearnSpeed, float Moment, float FuncIndent, float Bias)
    : NeuralLayer(NeuronsValue, PrevLayer, LearnSpeed, Moment, FuncIndent, Bias)
{

}

void OutputNeuralLayer::Forward(QVector<float> &inputSignals)
{
    NeuralLayer::Forward(inputSignals);
}

float OutputNeuralLayer::InitBack(QVector<float> &idealResult)
{
    float resultError = 0;
    float buf;
    for(int i = 0; i < idealResult.size(); ++i)
    {
        buf = outputs[i] - idealResult[i];
        layerDelta[i] = buf * ActivationFuncDerivative(outputs[i]);
        resultError += buf * buf;
    }
    prevLayer->Back(layerDelta);
    return resultError;
}
