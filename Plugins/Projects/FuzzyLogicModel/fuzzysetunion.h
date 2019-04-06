#ifndef FUZZYSETUNION_H
#define FUZZYSETUNION_H

#include "fuzzyset.h"

class FuzzySetUnion
{
public:
    FuzzySetUnion();

    void AddSet(IFuzzyLogicModel::IFuzzySet *set, float yLimit);
    float GetUnionCentroid(float resolution = 500);

private:
    QMap<IFuzzyLogicModel::IFuzzySet *, float> sets;
    float max;
    float min;

    float GetSetsMaxValue(float x);
};

#endif // FUZZYSETUNION_H
