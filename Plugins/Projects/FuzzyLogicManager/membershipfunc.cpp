#include "membershipfunc.h"

MembershipFunc::MembershipFunc(FuncType type, QList<float> definitionPoints)
{
    this->type = type;
    this->definitionPoints = definitionPoints;

    switch (type)
    {
        case IMembershipFunc::Triangular:
            type = definitionPoints.length() == 3 ? type : IMembershipFunc::Unknown;
            break;

        case IMembershipFunc::Trapezoidal:
            type = definitionPoints.length() == 4 ? type : IMembershipFunc::Unknown;
            break;

        default:
            type = IMembershipFunc::Unknown;
            break;
    }
}

IFuzzyLogicManager::IMembershipFunc::FuncType MembershipFunc::GetType()
{
    return type;
}

QList<float> MembershipFunc::GetDefinitionPoints()
{
    return definitionPoints;
}

TriangularMembershipFunc::TriangularMembershipFunc(IFuzzyLogicManager::IMembershipFunc::FuncType type, QList<float> definitionPoints)
    : MembershipFunc(type, definitionPoints)
{
    A = definitionPoints.at(0);
    B = definitionPoints.at(1);
    C = definitionPoints.at(2);
}

float TriangularMembershipFunc::GetValueY(float x)
{
    if(x == B)
    {
        return 1;
    }

    if(x <= A || x >= C)
    {
        return 0;
    }

    if(x < B)
    {
        return 1 - (B - x) / (B - A);
    }

    if(x < C)
    {
        return (C - x) / (C - B);
    }
}

float TriangularMembershipFunc::GetMin()
{
    return A;
}

float TriangularMembershipFunc::GetMax()
{
    return C;
}

TrapezoidalMembershipFunc::TrapezoidalMembershipFunc(IFuzzyLogicManager::IMembershipFunc::FuncType type, QList<float> definitionPoints)
    : MembershipFunc(type, definitionPoints)
{
    A = definitionPoints.at(0);
    B = definitionPoints.at(1);
    C = definitionPoints.at(2);
    D = definitionPoints.at(3);
}

float TrapezoidalMembershipFunc::GetValueY(float x)
{
    if(x >= B && x <= C)
    {
        return 1;
    }

    if(x < A || x > D)
    {
        return 0;
    }

    if(x < B)
    {
        return (A - x) / (B - A);
    }

    if(x < D)
    {
        return 1 - (C - x) / (D - C);
    }
}

float TrapezoidalMembershipFunc::GetMin()
{
    return A;
}

float TrapezoidalMembershipFunc::GetMax()
{
    return D;
}
