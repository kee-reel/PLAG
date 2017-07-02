#ifndef MAINMENUMODULE_H
#define MAINMENUMODULE_H

#include <QWidget>
#include <QDebug>
#include <QMap>
#include <QApplication>
#include <QJsonObject>

#include "imainmenumodule.h"
#include "pluginlinker.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class MainMenuModelPlugin : public QObject, IMainMenuPluginModel, IRootModelPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin IRootModelPlugin IMainMenuPluginModel)

// IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

// IModelPlugin interface
public:
    void AddDataManager(QObject *dataManager) override;
    void AddModel(QObject *model, MetaInfo *meta) override;
    void AddView(QObject *instance, MetaInfo *meta) override;
public slots:
    bool Open(IModelPlugin *model, QWidget *modelWidget) override;
    void RelatedModelClosed(IModelPlugin *model) override;
    void RelatedViewClosed(IViewPlugin *view) override;
    void Close() override;
signals:
    void OnClose(IModelPlugin *pointer);
    void OnClose();

// IRootModelPlugin interface
public:
    void AddPlugin(QObject *instance, QJsonObject *meta) override;
    void Open(QWidget *parentWidget) override;

// IMainMenuPluginModel interface
public:
    MenuItem *GetRootMenuItem() override;
    void RunItem(MenuItem *item, MetaInfo *viewMeta) override;

public:
    MainMenuModelPlugin();
    ~MainMenuModelPlugin();
private:
    void OpenChildView();

    QList< PluginInfo<IModelPlugin> > childModels;
    QList< PluginInfo<IViewPlugin> > views;

    QWidget *parentWidget;
    int activeViewId;
    int activeModelId;

    PluginLinker pluginLinker;
    MenuItem *rootMenuItem;
};
//! @}
#endif // MAINMENUMODULE_H
