#ifndef FUZZYLOGICMODEL_H
#define FUZZYLOGICMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "ifuzzylogicmodel.h"

#include "membershipfunc.h"
#include "inputvariable.h"
#include "outputvariable.h"
#include "fuzzyset.h"
#include "fuzzyrule.h"


// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views


//! addtogroup FuzzyLogicModel_imp
//! {
class FuzzyLogicModel : public
    QObject,
    IFuzzyLogicModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IModelPlugin
        IFuzzyLogicModel
    )

public:
    FuzzyLogicModel();
    ~FuzzyLogicModel();

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

signals:
    void OnClose(PluginInfo*);
    void OnClose();

    // IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    void Close() override;


private:
    PluginInfo *pluginInfo;

    // ISomePlugin *myReferencedPlugin;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;

private:
    // Write your internal methods here

    // IFuzzyLogicModel interface
public:
    virtual IMembershipFunc *MakeMembershipFunc(IMembershipFunc::FuncType type, QList<float> definitionPoints) const override;
    virtual IFuzzySet *MakeSet(QString name, IMembershipFunc *func) const override;
    virtual IInputVariable *MakeInputVariable(QString name, float min, float max) const override;
    virtual IOutputVariable *MakeOutputVariable(QString name, float min, float max) const override;
    virtual IFuzzyRule *MakeRule() override;
};
//! }
#endif // FUZZYLOGICMODEL_H
