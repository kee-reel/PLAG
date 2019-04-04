#include "fuzzyrule.h"

FuzzyRule::FuzzyRule()
{
}

void FuzzyRule::AddCondition(IFuzzyLogicModel::IInputVariable *variable, IFuzzyLogicModel::IFuzzySet *set)
{
    conditions.insertMulti(variable, set);
}

void FuzzyRule::AddConsequence(IFuzzyLogicModel::IOutputVariable *variable, IFuzzyLogicModel::IFuzzySet *set)
{
    consequences.insertMulti(variable, set);
}

QMap<IFuzzyLogicModel::IInputVariable *, IFuzzyLogicModel::IFuzzySet *> FuzzyRule::GetConditions()
{
    return conditions;
}

QMap<IFuzzyLogicModel::IOutputVariable*, IFuzzyLogicModel::IFuzzySet*> FuzzyRule::GetConsequences()
{
    return consequences;
}

QMap<IFuzzyLogicModel::IFuzzySet *, float> FuzzyRule::GetOutput()
{
    QMap<IFuzzyLogicModel::IFuzzySet *, float> output;
    float condMin = 1;
    auto condIter = conditions.begin();

    while(condIter != conditions.end())
    {
        float condTruth = condIter.key()->GetSetValue(condIter.value());
        condMin = condMin > condTruth ? condTruth : condMin;
        ++condIter;
    }

    foreach (auto consequence, consequences)
    {
        output.insert(consequence, condMin);
    }

    return output;
}
