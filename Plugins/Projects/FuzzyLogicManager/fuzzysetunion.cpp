#include "fuzzysetunion.h"

FuzzySetUnion::FuzzySetUnion()
{
}

void FuzzySetUnion::AddSet(IFuzzyLogicManager::IFuzzySet *set, float yLimit)
{
    float setMin = set->GetMin();
    float setMax = set->GetMax();

    if(sets.count() == 0)
    {
        min = setMin;
        max = setMax;
    }
    else
    {
        min = min > setMin ? setMin : min;
        max = max < setMax ? setMax : max;
    }

    sets.insert(set, yLimit);
}

float FuzzySetUnion::GetUnionCentroid(float resolution)
{
    const float dx = (max - min) / resolution;
    float x;
    float y;
    float area = 0;
    float xcentroid = 0;

    //scalar ycentroid = 0;
    for (int i = 0; i < resolution; ++i)
    {
        x = min + (i + 0.5) * dx;
        y = GetSetsMaxValue(x);
        xcentroid += y * x;
        //ycentroid += y * y;
        area += y;
    }

    //Final results not computed for efficiency
    //xcentroid /= area;
    //ycentroid /= 2 * area;
    //area *= dx;
    return xcentroid / area;
}

float FuzzySetUnion::GetSetsMaxValue(float x)
{
    float result = 0;
    auto iter = sets.begin();

    while(iter != sets.end())
    {
        float setValue = iter.key()->GetValueY(x);
        setValue = setValue > iter.value() ? iter.value() : setValue;
        result = result < setValue ? setValue : result;
        ++iter;
    }

    return result;
}
