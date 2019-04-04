#include "fuzzylogicmodel.h"

FuzzyLogicModel::FuzzyLogicModel() :
    PluginBase()
{
}

FuzzyLogicModel::~FuzzyLogicModel()
{
}

IFuzzyLogicModel::IMembershipFunc *FuzzyLogicModel::MakeMembershipFunc(IMembershipFunc::FuncType type, QList<float> definitionPoints) const
{
    switch (type)
    {
        case IFuzzyLogicModel::IMembershipFunc::Triangular:
            return new TriangularMembershipFunc(type, definitionPoints);
            break;

        case IFuzzyLogicModel::IMembershipFunc::Trapezoidal:
            return new TrapezoidalMembershipFunc(type, definitionPoints);
            break;
    }
}

IFuzzyLogicModel::IFuzzySet *FuzzyLogicModel::MakeSet(QString name, IMembershipFunc *func) const
{
    return new FuzzySet(name, func);
}

IFuzzyLogicModel::IInputVariable *FuzzyLogicModel::MakeInputVariable(QString name, float min, float max) const
{
    return new InputVariable(name, min, max);
}

IFuzzyLogicModel::IOutputVariable *FuzzyLogicModel::MakeOutputVariable(QString name, float min, float max) const
{
    return new OutputVariable(name, min, max);
}

IFuzzyLogicModel::IFuzzyRule *FuzzyLogicModel::MakeRule()
{
    return new FuzzyRule();
}
