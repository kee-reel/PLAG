#ifndef MAINMENUMODULE_H
#define MAINMENUMODULE_H

#include <QWidget>
#include <QDebug>
#include <QMap>
#include <QApplication>
#include <QJsonObject>

#include "imainmenumodule.h"
#include "pluginlinker.h"
#include "widgetstack.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class MainMenuModelPlugin : public QObject, IMainMenuModel, ICorePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin ICorePlugin IMainMenuModel)

// IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;
public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

// IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    void Close() override;
signals:
    void OnClose(PluginInfo *pointer);
    void OnClose();

// IRootModelPlugin interface
public:
    void AddPlugin(QObject *instance, QJsonObject *meta) override;
    void Run(QWidget *parentWidget) override;

// IMainMenuPluginModel interface
public:
    MenuItem *GetRootMenuItem() override;
    void RunItem(MenuItem *item, MetaInfo *itemMeta) override;

public:
    MainMenuModelPlugin();
    ~MainMenuModelPlugin();
private:
    void OpenChildView();

    QList<PluginInfo*> childModels;
    QList<PluginInfo*> views;
    PluginInfo *pluginInfo;
    WidgetStack *widgetStack;

    int activeViewId;
    int activeModelId;

    PluginLinker pluginLinker;
    MenuItem *rootMenuItem;

};
//! @}
#endif // MAINMENUMODULE_H
