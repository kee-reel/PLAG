#ifndef EMPTYPLUGINMODEL_H
#define EMPTYPLUGINMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "iemptypluginmodel.h"

class EmptyPluginModel : public QObject, IEmptyPluginModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginModel IEmptyPluginModel)

public:
    EmptyPluginModel();
    ~EmptyPluginModel();

private:
    IPluginModel *myParent;
    QWidget *myParentWidget;
    int myModelId;
    int activeViewId;
    int activeModelId;

    template <class T>
    struct PluginInfo
    {
        T *plugin;
        MetaInfo *meta;
    };

    QList< PluginInfo<IPluginModel> > childModelPlugins;
    QList< PluginInfo<IPluginView> > viewPlugins;

    // IPluginModel interface
public:
    virtual void AddChildPlugin(IPluginModel *, MetaInfo *);
    virtual void AddView(IPluginView *plugin, MetaInfo *meta);
    virtual void SetDataManager(QObject *);

    virtual bool Open(IPluginModel* parent, QWidget* parentWidget, int id);

public slots:
    virtual bool Close();
    virtual void ChildSelfClosed(int id);
    virtual QString GetError();

    // IEmptyPluginModel interface
public:
    virtual void TestFunc();   
};

#endif // EMPTYPLUGINMODEL_H
