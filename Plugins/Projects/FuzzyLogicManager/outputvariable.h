#ifndef OUTPUTVARIABLE_H
#define OUTPUTVARIABLE_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../Interfaces/ifuzzylogicmanager.h"

#include "fuzzysetunion.h"

class OutputVariable : public IFuzzyLogicManager::IOutputVariable
{
public:
    OutputVariable(QString name, float min, float max);

    // IVariable interface
public:
    virtual void AddSet(IFuzzyLogicManager::IFuzzySet *set) override;

    // IOutputVariable interface
public:
    virtual void AddInput(IFuzzyLogicManager::IInputVariable *variable) override;
    virtual void AddRule(IFuzzyLogicManager::IFuzzyRule *rule) override;
    virtual float GetOutput() override;

private:
    QMap<IFuzzyLogicManager::IFuzzySet*, float> setValues;

    QString name;
    float min;
    float max;

    QList<IFuzzyLogicManager::IInputVariable*> inputs;
    QList<IFuzzyLogicManager::IFuzzyRule*> rules;
};

#endif // OUTPUTVARIABLE_H
