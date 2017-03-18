#include "neurallayer.h"

NeuralLayer::NeuralLayer(int NeuronsValue, NeuralLayer *PrevLayer) : QObject()
{
    qDebug() << "NeuralLayer created";
    prevLayer = PrevLayer;
    nextLayer = NULL;

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
        float buf = 0;
        for(int prevLayerNeuron = 0; prevLayerNeuron < prevLayer->LayerSize(); ++prevLayerNeuron)
            buf += prevOutputs[prevLayerNeuron] * inputWeights[myLayerNeuron][prevLayerNeuron];
        outputs[myLayerNeuron] = ActivationFunc(buf);
    }

    if(nextLayer)
        nextLayer->Forward(outputs);
}

void NeuralLayer::Back(QVector<float> &nextLayerDelta)
{
    //qDebug() << "Back";
    for(int i = 0; i < LayerSize(); ++i)
    {
        currentLayerDelta[i] = (1 - outputs[i]) * outputs[i];
        for(int j = 0; j < nextLayer->LayerSize(); ++j)
        {
            currentLayerDelta[i] += outputWeights->at(j).at(i) * nextLayerDelta[j];
            float delta = 0.7 * nextLayerDelta[j] * outputs[i]; // TODO: Moment
            (*outputWeights)[j][i] += delta + 0.3 * nextLayer->weightsDelta[j][i];
            //qDebug() << "delta" << delta;
            nextLayer->weightsDelta[j][i] = delta;
        }
    }
    if(prevLayer)
        prevLayer->Back(currentLayerDelta);
}

InputNeuralLayer::InputNeuralLayer(int NeuronsValue) : NeuralLayer(NeuronsValue, NULL)
{

}

void InputNeuralLayer::Forward(QVector<float> &inputSignals)
{
    outputs = inputSignals;
    nextLayer->Forward(inputSignals);
}

void InputNeuralLayer::Back(QVector<float> &nextLayerDelta)
{
    NeuralLayer::Back(nextLayerDelta);
}

OutputNeuralLayer::OutputNeuralLayer(int NeuronsValue, NeuralLayer *PrevLayer) : NeuralLayer(NeuronsValue, PrevLayer)
{

}

void OutputNeuralLayer::Forward(QVector<float> &inputSignals)
{
    NeuralLayer::Forward(inputSignals);
    qDebug() << outputs[0];
}

float OutputNeuralLayer::InitBackpropagation(QVector<float> &idealResult)
{
    float resultError = 0;
    for(int i = 0; i < idealResult.size(); ++i)
    {
        currentLayerDelta[i] = (outputs[i] - idealResult[i]) * (1 - outputs[i]) * 0.6 * outputs[i];
        resultError += outputs[i] - idealResult[i];
    }
    prevLayer->Back(currentLayerDelta);
    return resultError;
}
