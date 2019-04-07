#ifndef MEMBERSHIPFUNC_H
#define MEMBERSHIPFUNC_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../Interfaces/ifuzzylogicmanager.h"

class MembershipFunc : public IFuzzyLogicManager::IMembershipFunc
{
public:
    MembershipFunc(IMembershipFunc::FuncType type, QList<float> definitionPoints);

    // IMembershipFunc interface
public:
    virtual float GetValueY(float x) = 0;
    virtual FuncType GetType() override;
    virtual QList<float> GetDefinitionPoints() override;
    virtual float GetMin() = 0;
    virtual float GetMax() = 0;

private:
    FuncType type;
    QList<float> definitionPoints;
};

class TriangularMembershipFunc : public MembershipFunc
{
public:
    TriangularMembershipFunc(IMembershipFunc::FuncType type, QList<float> definitionPoints);
    virtual float GetValueY(float x) override;
    virtual float GetMin() override;
    virtual float GetMax() override;

private:
    float A;
    float B;
    float C;
};

class TrapezoidalMembershipFunc : public MembershipFunc
{
public:
    TrapezoidalMembershipFunc(IMembershipFunc::FuncType type, QList<float> definitionPoints);
    virtual float GetValueY(float x) override;
    virtual float GetMin() override;
    virtual float GetMax() override;

private:
    float A;
    float B;
    float C;
    float D;

};

#endif // MEMBERSHIPFUNC_H
