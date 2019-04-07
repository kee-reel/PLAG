#ifndef FUZZYSETUNION_H
#define FUZZYSETUNION_H

#include "fuzzyset.h"

class FuzzySetUnion
{
public:
    FuzzySetUnion();

    void AddSet(IFuzzyLogicManager::IFuzzySet *set, float yLimit);
    float GetUnionCentroid(float resolution = 500);

private:
    QMap<IFuzzyLogicManager::IFuzzySet *, float> sets;
    float max;
    float min;

    float GetSetsMaxValue(float x);
};

#endif // FUZZYSETUNION_H
