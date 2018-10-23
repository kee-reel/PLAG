#include "fuzzylogicmodel.h"

FuzzyLogicModel::FuzzyLogicModel()
{
    // myReferencedPlugin = nullptr;
    openedView = nullptr;
    openedModel = nullptr;
    /*
    ui->setupUi(this);
    */
    OnAllSetup();
}

FuzzyLogicModel::~FuzzyLogicModel()
{
}

void FuzzyLogicModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void FuzzyLogicModel::OnAllSetup()
{
}

QString FuzzyLogicModel::GetLastError()
{
}

void FuzzyLogicModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    /* Select your reference plugin case and get it. For example:
        case PLUGINMODEL:{
            myReferencedPlugin = qobject_cast<ISomePlugin*>(pluginInfo->Instance);
            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not ISomePlugin.";
                return;
            }
            qDebug() << "ISomePlugin succesfully set.";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;
    */
    switch(pluginInfo->Meta->Type)
    {
        case VIEWPLUGIN:
        {
            relatedViewPlugins.append(pluginInfo);
            qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
            connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
        } break;

        case MODELPLUGIN:
        {
            relatedModelPlugins.append(pluginInfo);
            qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;

        case COREPLUGIN:
        {
        } break;

        case DATAMANAGERPLUGIN:
        {
        } break;
    }
}

void FuzzyLogicModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

bool FuzzyLogicModel::Open(IModelPlugin *parent)
{
    qDebug() << "FuzzyLogicModel open.";

    if(relatedViewPlugins.count() == 0)
    {
        qDebug() << "!FuzzyLogicModel hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "FuzzyLogicModel opens related view " << openedView->Meta->Name;

    if(!openedView->Plugin.view->Open(this))
    {
        qDebug() << "!Can't open first view!";
        openedView = nullptr;
        return false;
    }

    return true;
}

void FuzzyLogicModel::Close()
{
    qDebug() << "FuzzyLogicModel close.";

    if(openedView != nullptr && !openedView->Plugin.view->Close())
    {
        qDebug() << "View plugin" << openedView->Meta->Name
                 << "not closed, but model closing anyway.";
    }

    if(openedModel != nullptr)
        openedView->Plugin.view->Close();

    openedView = nullptr;
    openedModel = nullptr;
    emit OnClose(pluginInfo);
    emit OnClose();
}


IFuzzyLogicModel::IMembershipFunc *FuzzyLogicModel::MakeMembershipFunc(IMembershipFunc::FuncType type, QList<float> definitionPoints) const
{
    switch (type)
    {
        case IFuzzyLogicModel::IMembershipFunc::Triangular:
            return new TriangularMembershipFunc(type, definitionPoints);
            break;

        case IFuzzyLogicModel::IMembershipFunc::Trapezoidal:
            return new TrapezoidalMembershipFunc(type, definitionPoints);
            break;
    }
}

IFuzzyLogicModel::IFuzzySet *FuzzyLogicModel::MakeSet(QString name, IMembershipFunc *func) const
{
    return new FuzzySet(name, func);
}

IFuzzyLogicModel::IInputVariable *FuzzyLogicModel::MakeInputVariable(QString name, float min, float max) const
{
    return new InputVariable(name, min, max);
}

IFuzzyLogicModel::IOutputVariable *FuzzyLogicModel::MakeOutputVariable(QString name, float min, float max) const
{
    return new OutputVariable(name, min, max);
}

IFuzzyLogicModel::IFuzzyRule *FuzzyLogicModel::MakeRule()
{
    return new FuzzyRule();
}
