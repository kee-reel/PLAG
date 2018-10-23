#ifndef FUZZYSET_H
#define FUZZYSET_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "ifuzzylogicmodel.h"

class FuzzySet : public IFuzzyLogicModel::IFuzzySet
{
public:
    FuzzySet(QString name, IFuzzyLogicModel::IMembershipFunc *func);

    // IFuzzySet interface
public:
    virtual QString GetName() override;
    virtual float GetValueY(float x) override;

private:
    QString name;
    IFuzzyLogicModel::IMembershipFunc *func;

    // IFuzzySet interface
public:
    virtual float GetMin() override;
    virtual float GetMax() override;
};

#endif // FUZZYSET_H
