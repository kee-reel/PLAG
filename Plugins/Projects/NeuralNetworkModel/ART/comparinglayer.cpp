#include "comparinglayer.h"

ComparingLayer::ComparingLayer(int size, NetworkParams *params)
{
    this->params = params;
    output.resize(size);
}

void ComparingLayer::Input(QVector<int> &input)
{
    this->input = &input;
    for(int i = 0; i < output.length(); ++i)
        output[i] = input[i];
    qDebug() << "C:" << output;
    recognitionLayer->Input(output);
}

void ComparingLayer::Response(QVector<int> &response)
{
    QVector<int> newVector;
    newVector.resize(response.length());
    int overlapValues = 0;
    for(int i = 0; i < response.length(); ++i)
    {
        newVector[i] = (response[i] && input->at(i));
        if(response[i] == input->at(i)) ++overlapValues;
    }
    float buf = overlapValues / (float)response.length();
    qDebug() << "C:" << newVector;
    qDebug() << "Ro:" << buf;
    if(params->similarity > buf)
        recognitionLayer->CreateNewNeuron(*input);
    else
        recognitionLayer->RefreshActiveNeuron(newVector);
}
