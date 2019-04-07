#ifndef FUZZYSET_H
#define FUZZYSET_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../Interfaces/ifuzzylogicmanager.h"

class FuzzySet : public IFuzzyLogicManager::IFuzzySet
{
public:
    FuzzySet(QString name, IFuzzyLogicManager::IMembershipFunc *func);

    // IFuzzySet interface
public:
    virtual QString GetName() override;
    virtual float GetValueY(float x) override;

private:
    QString name;
    IFuzzyLogicManager::IMembershipFunc *func;

    // IFuzzySet interface
public:
    virtual float GetMin() override;
    virtual float GetMax() override;
};

#endif // FUZZYSET_H
