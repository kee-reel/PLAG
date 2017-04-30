#ifndef ARTNETWORK_H
#define ARTNETWORK_H

#include <QVector>

struct NetworkParams{
    float similarity;
};

class ARTNetwork
{
    class RecognitionLayer
    {

    };

    class ComparingLayer
    {
        // Input x
        // Answer p
        // Modulator g1
    public:
        void Input(QVector<int> input);

    signals:
        OutputSignal(QVector<int> output);
    };



public:
    ARTNetwork();

};

#endif // ARTNETWORK_H
