#include "inputvariable.h"

InputVariable::InputVariable(QString name, float min, float max)
{
    this->name = name;
    this->min = min;
    this->max = max;
}

void InputVariable::AddSet(IFuzzyLogicManager::IFuzzySet *set)
{
    setValues.insert(set, 0);
}

void InputVariable::SetValue(float value)
{
    // Clamp value.
    this->value = value < min ? min :
                  value > max ? max : value;
    // Update sets values.
    auto iter = setValues.begin();

    while(iter != setValues.end())
    {
        float value = iter.key()->GetValueY(this->value);
        setValues[iter.key()] = value;
        ++iter;
    }
}

QList<float> InputVariable::GetSetsValues()
{
    return setValues.values();
}

float InputVariable::GetSetValue(IFuzzyLogicManager::IFuzzySet *set)
{
    return setValues.contains(set) ? setValues.value(set) : 0;
}
