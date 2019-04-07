#include "fuzzyrule.h"

FuzzyRule::FuzzyRule()
{
}

void FuzzyRule::AddCondition(IFuzzyLogicManager::IInputVariable *variable, IFuzzyLogicManager::IFuzzySet *set)
{
    conditions.insertMulti(variable, set);
}

void FuzzyRule::AddConsequence(IFuzzyLogicManager::IOutputVariable *variable, IFuzzyLogicManager::IFuzzySet *set)
{
    consequences.insertMulti(variable, set);
}

QMap<IFuzzyLogicManager::IInputVariable *, IFuzzyLogicManager::IFuzzySet *> FuzzyRule::GetConditions()
{
    return conditions;
}

QMap<IFuzzyLogicManager::IOutputVariable*, IFuzzyLogicManager::IFuzzySet*> FuzzyRule::GetConsequences()
{
    return consequences;
}

QMap<IFuzzyLogicManager::IFuzzySet *, float> FuzzyRule::GetOutput()
{
    QMap<IFuzzyLogicManager::IFuzzySet *, float> output;
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
