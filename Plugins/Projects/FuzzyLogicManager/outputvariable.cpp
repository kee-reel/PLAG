#include "outputvariable.h"

OutputVariable::OutputVariable(QString name, float min, float max)
{
    this->name = name;
    this->min = min;
    this->max = max;
}

void OutputVariable::AddSet(IFuzzyLogicManager::IFuzzySet *set)
{
    setValues.insert(set, 0);
}

void OutputVariable::AddInput(IFuzzyLogicManager::IInputVariable *variable)
{
    inputs.append(variable);
}

void OutputVariable::AddRule(IFuzzyLogicManager::IFuzzyRule *rule)
{
    rules.append(rule);
}

float OutputVariable::GetOutput()
{
    auto iter = setValues.begin();

    while(iter != setValues.end())
    {
        setValues[iter.key()] = 0;
        ++iter;
    }

    foreach (auto rule, rules)
    {
        auto ruleMap = rule->GetOutput();
        auto ruleIter = ruleMap.begin();

        while(ruleIter != ruleMap.end())
        {
            auto set = ruleIter.key();

            if(setValues.contains(set))
            {
                float value = ruleIter.value();
                setValues[set] = setValues[set] < value ? value : setValues[set];
            }

            ++ruleIter;
        }
    }

    float maxSet = 0;
    auto setIter = setValues.begin();
    FuzzySetUnion setUnion;

    while(setIter != setValues.end())
    {
        setUnion.AddSet(setIter.key(), setIter.value());
        float setValue = setIter.value();
        //        qDebug() << "Set = " << setValue;
        maxSet = setValue > maxSet ? setValue : maxSet;
        ++setIter;
    }

    float centroid = setUnion.GetUnionCentroid();
    return centroid;
}
