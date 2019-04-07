#ifndef COMPARINGLAYER_H
#define COMPARINGLAYER_H

#include <QVector>
#include <QDebug>

#include "parameters.h"
#include "ART/recognitionlayer.h"

class RecognitionLayer;
class ComparingLayer
{
protected:
    typedef Parameters::ART::NetworkParams NetworkParams;
public:
    NetworkParams *params;
    QVector<int> *input;
    QVector<int> output;
    RecognitionLayer *recognitionLayer;

    ComparingLayer(int size, NetworkParams *params);

    void Input(QVector<int> &input);
    void Response(QVector<int> &response);
};

#endif // COMPARINGLAYER_H
