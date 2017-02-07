#ifndef EMPTYMODULE_H
#define EMPTYMODULE_H

#include <QObject>
#include <QDebug>

#include "ipluginmodel.h"
#include "mainwindow.h"

class EmptyModule : public QObject, IPluginModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginModel)

public:
    EmptyModule();
    ~EmptyModule();

private:
    MainWindow* mainWindow;
    QMap<IPluginModel*, MetaInfo*> childPlugins;

    // IPlugin interface
public:
    void DoSomething() override;
    void AddChildPlugin(IPluginModel *plugin, MetaInfo *module) override;
    void AddDBTool(QObject*DBTool) override;

    bool Open(QWidget *parent) override;
    bool Close() override;
    QString GetError() override;
};

#endif // EMPTYMODULE_H
