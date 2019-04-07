#include "fuzzylogicmanager.h"

FuzzyLogicManager::FuzzyLogicManager() :
    PluginBase()
{
}

FuzzyLogicManager::~FuzzyLogicManager()
{
}

IFuzzyLogicManager::IMembershipFunc *FuzzyLogicManager::MakeMembershipFunc(IMembershipFunc::FuncType type, QList<float> definitionPoints) const
{
    switch (type)
    {
        case IFuzzyLogicManager::IMembershipFunc::Triangular:
            return new TriangularMembershipFunc(type, definitionPoints);
            break;

        case IFuzzyLogicManager::IMembershipFunc::Trapezoidal:
            return new TrapezoidalMembershipFunc(type, definitionPoints);
            break;
    }
}

IFuzzyLogicManager::IFuzzySet *FuzzyLogicManager::MakeSet(QString name, IMembershipFunc *func) const
{
    return new FuzzySet(name, func);
}

IFuzzyLogicManager::IInputVariable *FuzzyLogicManager::MakeInputVariable(QString name, float min, float max) const
{
    return new InputVariable(name, min, max);
}

IFuzzyLogicManager::IOutputVariable *FuzzyLogicManager::MakeOutputVariable(QString name, float min, float max) const
{
    return new OutputVariable(name, min, max);
}

IFuzzyLogicManager::IFuzzyRule *FuzzyLogicManager::MakeRule()
{
    return new FuzzyRule();
}
