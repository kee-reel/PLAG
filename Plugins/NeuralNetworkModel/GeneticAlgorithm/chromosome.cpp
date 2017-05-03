#include "chromosome.h"

Chromosome::Chromosome(int genesCount, int geneCapacity)
{
    this->genesCount = genesCount;
    this->geneCapacity = geneCapacity;
    genes.resize(genesCount);
    for(int i = 0; i < genes.size(); ++i)
        genes[i] = (qrand() % (geneCapacity * 10000)) / 10000.;
}

void Chromosome::ModificateBit(int value, int pos)
{

}

Chromosome *Chromosome::Breed(Chromosome *mother, Chromosome *father, bool withMutation)
{
    Chromosome *child = new Chromosome(mother->genesCount, mother->geneCapacity);
    int turncatePos = (qrand() % mother->genesCount) + 1;
    for(int i = 0; i < child->genes.size(); ++i)
        child->genes[i] = (i < turncatePos) ? mother->genes[i] : father->genes[i];
    if(withMutation)
        child->genes[qrand() % child->genesCount] = (qrand() % (child->geneCapacity * 10000)) / 10000.;
    return child;
}
