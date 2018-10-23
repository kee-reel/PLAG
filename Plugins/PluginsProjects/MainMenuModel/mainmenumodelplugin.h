#ifndef MAINMENUMODULE_H
#define MAINMENUMODULE_H

#include <QWidget>
#include <QDebug>
#include <QMap>
#include <QApplication>
#include <QJsonObject>

#include "../../PluginsCommon/plugin_base.h"
#include "../../../Application/icoreplugin.h"
#include "../../PluginsInterfaces/imainmenumodule.h"

#include "pluginlinker.h"
#include "widgetstack.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class MainMenuModelPlugin : public PluginBase, IMainMenuModel, ICorePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(/*IModelPlugin*/ ICorePlugin /*IMainMenuModel*/)

public:
    MainMenuModelPlugin();
    virtual ~MainMenuModelPlugin() override;

    // IRootModelPlugin interface
public:
    virtual void addPlugins(const QVector<QWeakPointer<IPluginHandler>>& pluginHandlers) override;
    virtual void start(QWidget *parentWidget) override;

    // IPlugin interface
//public:
//    void SetPluginInfo(PluginInfo *pluginInfo) override;
//    void OnAllSetup() override;
//    QString GetLastError() override;
//    void AddReferencePlugin(PluginInfo *pluginInfo) override;
//public slots:
//    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

    // IModelPlugin interface
//public slots:
//    bool Open(IModelPlugin *model) override;
//    void Close() override;
//signals:
//    void OnClose(PluginInfo *pointer);
//    void OnClose();

//    // IMainMenuPluginModel interface
//public:
//    MenuItem *GetRootMenuItem() override;
//    void RunItem(MenuItem *item, MetaInfo *itemMeta) override;

//private:
//    void OpenChildView();

private:
//    QList<PluginInfo*> childModels;
//    QList<PluginInfo*> views;
//    PluginInfo *pluginInfo;
//    WidgetStack *widgetStack;

//    int activeViewId;
//    int activeModelId;

    PluginLinker pluginLinker;
//    MenuItem *rootMenuItem;

    // IMainMenuModel interface
public:
    QVector<const IMenuItem *> getMenuItems();
    void openItem(IMenuItem *item, MetaInfo *viewMeta);
};
//! @}
#endif // MAINMENUMODULE_H
