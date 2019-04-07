#ifndef FUZZYRULE_H
#define FUZZYRULE_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../Interfaces/ifuzzylogicmanager.h"

class FuzzyRule : public IFuzzyLogicManager::IFuzzyRule
{
public:
    FuzzyRule();

    // IFuzzyRule interface
public:
    virtual void AddCondition(IFuzzyLogicManager::IInputVariable *variable, IFuzzyLogicManager::IFuzzySet *set) override;
    virtual void AddConsequence(IFuzzyLogicManager::IOutputVariable *variable, IFuzzyLogicManager::IFuzzySet *set) override;
    virtual QMap<IFuzzyLogicManager::IInputVariable*, IFuzzyLogicManager::IFuzzySet*> GetConditions() override;
    virtual QMap<IFuzzyLogicManager::IOutputVariable*, IFuzzyLogicManager::IFuzzySet*> GetConsequences() override;
    virtual QMap<IFuzzyLogicManager::IFuzzySet *, float> GetOutput() override;

private:
    QMap<IFuzzyLogicManager::IInputVariable*, IFuzzyLogicManager::IFuzzySet*> conditions;
    QMap<IFuzzyLogicManager::IOutputVariable*, IFuzzyLogicManager::IFuzzySet*> consequences;
};

#endif // FUZZYRULE_H
