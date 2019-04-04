#ifndef INPUTVARIABLE_H
#define INPUTVARIABLE_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../PluginsInterfaces/ifuzzylogicmodel.h"

class InputVariable : public IFuzzyLogicModel::IInputVariable
{
public:
    InputVariable(QString name, float min, float max);

    // IVariable interface
public:
    virtual void AddSet(IFuzzyLogicModel::IFuzzySet *set) override;

    // IInputVariable interface
public:
    virtual void SetValue(float value) override;
    virtual QList<float> GetSetsValues() override;
    virtual float GetSetValue(IFuzzyLogicModel::IFuzzySet*set) override;
private:
    QMap<IFuzzyLogicModel::IFuzzySet*, float> setValues;

    QString name;
    float min;
    float max;
    float value;


};

#endif // INPUTVARIABLE_H
