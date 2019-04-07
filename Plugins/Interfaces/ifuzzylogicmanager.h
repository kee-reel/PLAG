#ifndef IFuzzyLogicManager_H
#define IFuzzyLogicManager_H

#include <QtCore>

//!  \defgroup FuzzyLogic FuzzyLogic
//!      \ingroup Plugins
//!  \defgroup FuzzyLogic_int Interface
//!      \ingroup FuzzyLogic
//!  \defgroup FuzzyLogic_imp Implementation
//!      \ingroup FuzzyLogic
//!  \defgroup FuzzyLogic_dep Dependent plugins
//!      \ingroup FuzzyLogic

//!  \addtogroup FuzzyLogic_int
//!  \{
class IFuzzyLogicManager
{
public:

    class IMembershipFunc
    {
    public:
        enum FuncType
        {
            Triangular,
            Trapezoidal,

            Unknown
        };
        virtual float GetValueY(float x) = 0;
        virtual FuncType GetType() = 0;
        virtual QList<float> GetDefinitionPoints() = 0;
        virtual float GetMin() = 0;
        virtual float GetMax() = 0;
    };

    class IFuzzySet
    {
    public:
        virtual QString GetName() = 0;
        virtual float GetValueY(float x) = 0;
        virtual float GetMin() = 0;
        virtual float GetMax() = 0;
    };

    class IVariable
    {
    public:
        virtual void AddSet(IFuzzySet *set) = 0;
    };

    class IInputVariable : public IVariable
    {
    public:
        virtual void SetValue(float value) = 0;
        virtual QList<float> GetSetsValues() = 0;
        virtual float GetSetValue(IFuzzyLogicManager::IFuzzySet*set) = 0;
    };

    class IFuzzyRule;
    class IOutputVariable : public IVariable
    {
    public:
        enum DefuzzyficationFuncType
        {
            Mamdani,
        };

        virtual void AddInput(IInputVariable *variable) = 0;
        virtual void AddRule(IFuzzyRule *rule) = 0;
        virtual float GetOutput() = 0;
    };

    class IFuzzyRule
    {
    public:
        virtual void AddCondition(IInputVariable *variable, IFuzzySet *set) = 0;
        virtual void AddConsequence(IOutputVariable *variable, IFuzzySet *set) = 0;
        virtual QMap<IFuzzyLogicManager::IInputVariable*, IFuzzyLogicManager::IFuzzySet*> GetConditions() = 0;
        virtual QMap<IFuzzyLogicManager::IOutputVariable*, IFuzzyLogicManager::IFuzzySet*> GetConsequences() = 0;
        virtual QMap<IFuzzySet *, float> GetOutput() = 0;
    };

    virtual IMembershipFunc *MakeMembershipFunc(IMembershipFunc::FuncType type, QList<float> definitionPoints) const = 0;
    virtual IFuzzySet *MakeSet(QString name, IMembershipFunc *func) const = 0;
    virtual IInputVariable *MakeInputVariable(QString name, float min, float max) const = 0;
    virtual IOutputVariable *MakeOutputVariable(QString name, float min, float max) const = 0;
    virtual IFuzzyRule *MakeRule() = 0;
};
//!  \}
Q_DECLARE_INTERFACE(IFuzzyLogicManager, "IFuzzyLogicManager")
#endif // IFuzzyLogicManager_H

//InputLinguisticVariable* x = new InputLinguisticVariable("x",-10,10);
//TrapezoidalFuzzySet* negative = new TrapezoidalFuzzySet("Negative", -10, -10, -1, 0);
//TriangularFuzzySet* zero = new TriangularFuzzySet("Zero", -1,0,1);
//TrapezoidalFuzzySet* positive = new TrapezoidalFuzzySet("Positive", 0,1,10,10);
//x->addSet(negative);
//x->addSet(zero);
//x->addSet(positive);

//MamdaniOutputVariable* y = new MamdaniOutputVariable("y", -3,3);
//TriangularFuzzySet* negative_2 = new TriangularFuzzySet("Negative", -2, -1, 0);
//TriangularFuzzySet* positive_2 = new TriangularFuzzySet("Positive", 0,1,2);
//TriangularFuzzySet* largenegative = new TriangularFuzzySet("Largenegative", -3, -2, -1);
//TriangularFuzzySet* largepositive = new TriangularFuzzySet("Largepositive",1,2,3);
//y->addSet(negative_2);
//y->addSet(zero);
//y->addSet(positive_2);
//y->addSet(largenegative);
//y->addSet(largepositive);

//InputLinguisticVariable* z = new InputLinguisticVariable("z", -10, 10);
//z->addSet(negative);
//z->addSet(zero);
//z->addSet(positive);

//calculator->addInputVar(x);
//calculator->setOutputVar(y);
//calculator->addInputVar(z);
////adding rules
//calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Negative THEN y IS Negative"));
//calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Negative THEN y IS Largenegative")
