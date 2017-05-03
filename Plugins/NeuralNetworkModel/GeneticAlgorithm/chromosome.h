#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <QVector>
#include <QByteArray>

class Chromosome
{
public:
    float fitness;
    QVector<float> genes;
    int genesCount;
    int geneCapacity;

    Chromosome(int genesCount, int geneCapacity);
    int GetValue();

    static Chromosome *Breed(Chromosome *mother, Chromosome *father, bool withMutation = true);
    static void ModificateBit(int value, int pos);
};

#endif // CHROMOSOME_H
