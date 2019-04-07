#ifndef FuzzyLogic_H
#define FuzzyLogic_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/ifuzzylogicmanager.h"

#include "membershipfunc.h"
#include "inputvariable.h"
#include "outputvariable.h"
#include "fuzzyset.h"
#include "fuzzyrule.h"


// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views


//! \addtogroup FuzzyLogic_imp
//! \{
class FuzzyLogicManager : public
    PluginBase,
    IFuzzyLogicManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IFuzzyLogicManager
    )

public:
    FuzzyLogicManager();
    ~FuzzyLogicManager();

    // IFuzzyLogicManager interface
public:
    virtual IMembershipFunc *MakeMembershipFunc(IMembershipFunc::FuncType type, QList<float> definitionPoints) const override;
    virtual IFuzzySet *MakeSet(QString name, IMembershipFunc *func) const override;
    virtual IInputVariable *MakeInputVariable(QString name, float min, float max) const override;
    virtual IOutputVariable *MakeOutputVariable(QString name, float min, float max) const override;
    virtual IFuzzyRule *MakeRule() override;
};
//! \}
#endif // FuzzyLogic_H
