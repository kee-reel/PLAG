#ifndef EMPTYMODULE_H
#define EMPTYMODULE_H

#include <QObject>
#include <QDebug>

#include "iemptypluginmodel.h"

class EmptyPluginView : public QObject, IPluginView
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginView)

public:
    EmptyPluginView();
    ~EmptyPluginView();

private:
    IEmptyPluginModel* model;

    // IPluginView interface
public:
    virtual void SetModel(QObject* model);
    virtual bool Open(QWidget *parent);
    virtual bool Close();
};

#endif // EMPTYMODULE_H
