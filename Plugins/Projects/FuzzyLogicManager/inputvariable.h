#ifndef INPUTVARIABLE_H
#define INPUTVARIABLE_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../Interfaces/ifuzzylogicmanager.h"

class InputVariable : public IFuzzyLogicManager::IInputVariable
{
public:
    InputVariable(QString name, float min, float max);

    // IVariable interface
public:
    virtual void AddSet(IFuzzyLogicManager::IFuzzySet *set) override;

    // IInputVariable interface
public:
    virtual void SetValue(float value) override;
    virtual QList<float> GetSetsValues() override;
    virtual float GetSetValue(IFuzzyLogicManager::IFuzzySet*set) override;
private:
    QMap<IFuzzyLogicManager::IFuzzySet*, float> setValues;

    QString name;
    float min;
    float max;
    float value;


};

#endif // INPUTVARIABLE_H
