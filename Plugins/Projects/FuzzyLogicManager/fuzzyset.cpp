#include "fuzzyset.h"

FuzzySet::FuzzySet(QString name, IFuzzyLogicManager::IMembershipFunc *func)
{
    this->name = name;
    this->func = func;
}

QString FuzzySet::GetName()
{
    return name;
}

float FuzzySet::GetValueY(float x)
{
    return func->GetValueY(x);
}

float FuzzySet::GetMin()
{
    return func->GetMin();
}

float FuzzySet::GetMax()
{
    return func->GetMax();
}
