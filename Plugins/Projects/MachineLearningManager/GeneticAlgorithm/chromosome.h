#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <QVector>
#include <QByteArray>

#include "parameters.h"

class Chromosome
{
public:
    float fitness;
    QVector<float> genes;
    Parameters::GeneticAlgorithmParams::Parameters *params;

    Chromosome(Parameters::GeneticAlgorithmParams::Parameters *params);
    int GetValue();

    static Chromosome *Breed(Chromosome *mother, Chromosome *father, bool withMutation = true);
    static void ModificateBit(int value, int pos);
};

#endif // CHROMOSOME_H
