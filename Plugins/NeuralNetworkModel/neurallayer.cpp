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
    currentLayerDelta.resize(NeuronsValue);
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
            inputWeights[i][j] = -3 + ((float)(qrand()%600))/100;
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
        outputs[myLayerNeuron] = ActivationFunc(outputs[myLayerNeuron] + bias);
    }

    if(nextLayer)
        nextLayer->Forward(outputs);
}

void NeuralLayer::Back(QVector<float> &nextLayerDelta)
{
    float delta;
    for(int i = 0; i < LayerSize(); ++i)
    {
        currentLayerDelta[i] = ActivationFuncDerivative(outputs[i] + bias);
        for(int j = 0; j < nextLayer->LayerSize(); ++j)
        {
            currentLayerDelta[i] += outputWeights->at(j).at(i) * nextLayerDelta[j];
            delta = learnSpeed * nextLayerDelta[j] * outputs[i] + moment * nextLayer->weightsDelta[j][i]; // TODO: Moment
            (*outputWeights)[j][i] -= delta;
            nextLayer->weightsDelta[j][i] = delta;
        }
    }
    if(prevLayer)
        prevLayer->Back(currentLayerDelta);
}

InputNeuralLayer::InputNeuralLayer(int NeuronsValue, float LearnSpeed, float Moment, float FuncIndent, float Bias)
    : NeuralLayer(NeuronsValue, NULL, LearnSpeed, Moment, FuncIndent, Bias)
{

}

void InputNeuralLayer::Forward(QVector<float> &inputSignals)
{
    for(int i = 0; i < LayerSize(); ++i)
        inputSignals[i] += bias;
    outputs = inputSignals;
    nextLayer->Forward(inputSignals);
}

void InputNeuralLayer::Back(QVector<float> &nextLayerDelta)
{
    NeuralLayer::Back(nextLayerDelta);
}

OutputNeuralLayer::OutputNeuralLayer(int NeuronsValue, NeuralLayer *PrevLayer, float LearnSpeed, float Moment, float FuncIndent, float Bias)
    : NeuralLayer(NeuronsValue, PrevLayer, LearnSpeed, Moment, FuncIndent, Bias)
{

}

void OutputNeuralLayer::Forward(QVector<float> &inputSignals)
{
    NeuralLayer::Forward(inputSignals);
    qDebug() << "Out" << outputs[0];
}

float OutputNeuralLayer::InitBackpropagation(QVector<float> &idealResult)
{
    float resultError = 0;
    for(int i = 0; i < idealResult.size(); ++i)
    {
        currentLayerDelta[i] = (idealResult[i] - outputs[i]) * ActivationFuncDerivative(outputs[i] + bias);
        resultError += outputs[i] - idealResult[i];
    }
    prevLayer->Back(currentLayerDelta);
    return resultError;
}
