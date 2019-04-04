#ifndef FUZZYRULE_H
#define FUZZYRULE_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../PluginsInterfaces/ifuzzylogicmodel.h"

class FuzzyRule : public IFuzzyLogicModel::IFuzzyRule
{
public:
    FuzzyRule();

    // IFuzzyRule interface
public:
    virtual void AddCondition(IFuzzyLogicModel::IInputVariable *variable, IFuzzyLogicModel::IFuzzySet *set) override;
    virtual void AddConsequence(IFuzzyLogicModel::IOutputVariable *variable, IFuzzyLogicModel::IFuzzySet *set) override;
    virtual QMap<IFuzzyLogicModel::IInputVariable*, IFuzzyLogicModel::IFuzzySet*> GetConditions() override;
    virtual QMap<IFuzzyLogicModel::IOutputVariable*, IFuzzyLogicModel::IFuzzySet*> GetConsequences() override;
    virtual QMap<IFuzzyLogicModel::IFuzzySet *, float> GetOutput() override;

private:
    QMap<IFuzzyLogicModel::IInputVariable*, IFuzzyLogicModel::IFuzzySet*> conditions;
    QMap<IFuzzyLogicModel::IOutputVariable*, IFuzzyLogicModel::IFuzzySet*> consequences;
};

#endif // FUZZYRULE_H
