#include "chromosome.h"

Chromosome::Chromosome(Parameters::GeneticAlgorithmParams::Parameters *params)
{
    this->params = params;
    genes.resize(params->genesCount);
    float range = params->maxRange - params->minRange;
    for(int i = 0; i < genes.size(); ++i)
        genes[i] = params->minRange + (qrand()/double(RAND_MAX)) * range;
}

void Chromosome::ModificateBit(int value, int pos)
{

}

Chromosome *Chromosome::Breed(Chromosome *mother, Chromosome *father, bool withMutation)
{
    Chromosome *child = new Chromosome(mother->params);
    int turncatePos = (qrand() % mother->params->genesCount) + 1;
    for(int i = 0; i < child->genes.size(); ++i)
        child->genes[i] = (i < turncatePos) ? mother->genes[i] : father->genes[i];
    float range = mother->params->maxRange - mother->params->minRange;
    if(withMutation)
        child->genes[qrand() % child->params->genesCount] = mother->params->minRange + (qrand()/double(RAND_MAX)) * range;
    return child;
}
