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
    QMap<IPluginModel*, MetaInfo*> childPlugins;
    QMap<IPluginView*, MetaInfo*> viewPlugins;
    IPluginView* activeView;

    QWidget* parent;

    // IPluginModel interface
public:
    virtual void AddChildPlugin(IPluginModel *, MetaInfo *);
    virtual void SetDataManager(QObject *);
    virtual void AddView(IPluginView *plugin, MetaInfo *meta);
    virtual bool Open(QWidget *parent);
    virtual bool Close();
    virtual QString GetError();

    // IEmptyPluginModel interface
public:
    virtual void TestFunc();   
};

#endif // EMPTYPLUGINMODEL_H
