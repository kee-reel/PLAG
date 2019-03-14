#ifndef OUTPUTVARIABLE_H
#define OUTPUTVARIABLE_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "ifuzzylogicmodel.h"

#include "fuzzysetunion.h"

class OutputVariable : public IFuzzyLogicModel::IOutputVariable
{
public:
    OutputVariable(QString name, float min, float max);

    // IVariable interface
public:
    virtual void AddSet(IFuzzyLogicModel::IFuzzySet *set) override;

    // IOutputVariable interface
public:
    virtual void AddInput(IFuzzyLogicModel::IInputVariable *variable) override;
    virtual void AddRule(IFuzzyLogicModel::IFuzzyRule *rule) override;
    virtual float GetOutput() override;

private:
    QMap<IFuzzyLogicModel::IFuzzySet*, float> setValues;

    QString name;
    float min;
    float max;

    QList<IFuzzyLogicModel::IInputVariable*> inputs;
    QList<IFuzzyLogicModel::IFuzzyRule*> rules;
};

#endif // OUTPUTVARIABLE_H
