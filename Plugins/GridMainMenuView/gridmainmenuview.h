#ifndef GRIDMAINMENUVIEW_H
#define GRIDMAINMENUVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QLayout>
#include <QPushButton>
#include <QSpacerItem>

#include "igridmainmenuview.h"
#include "../MainMenuModelPlugin/imainmenumodule.h"
#include "menuitem.h"
#include "aspectawaregridlayout.h"

namespace Ui {
class Form;
}

//! addtogroup GridMainMenuView_imp
//! {
class GridMainMenuView : public QWidget, IGridMainMenuView
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IViewPlugin
            IGridMainMenuView
            )

public:
    explicit GridMainMenuView(QWidget *parent = 0);
    ~GridMainMenuView();

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

    // IViewPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    bool Close() override;


private:
    PluginInfo *pluginInfo;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;

private:
    Ui::Form *ui;
    AspectAwareGridLayout *layout;
    IMainMenuModel *mainMenu;
    IMainMenuModel::MenuItem *rootMenuItem;
    QList<MenuItem*> items;

private slots:
    void RunMenuItem(int id);
    QString FormatMenuItemName(QString name);

signals:
    void OnOpen(QWidget *);
};
//! }
#endif // GRIDMAINMENUVIEW_H
