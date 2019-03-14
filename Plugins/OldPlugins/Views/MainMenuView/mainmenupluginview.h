#ifndef MAINMENUPLUGINVIEW_H
#define MAINMENUPLUGINVIEW_H

#include <QLayout>
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include "../../Models/MainMenuModel/imainmenumodule.h"
#include "menuitem.h"
#include "ui_mainform.h"
namespace Ui {
class MainForm;
}

//! \defgroup MainMenuPluginView
//!     \ingroup MainMenuPlugin_rel_v
//! \defgroup MainMenuPluginView_imp Implementation
//!     \ingroup MainMenuPluginView

//! \addtogroup MainMenuPluginView_imp
//! \{
class MainMenuPluginView : public QWidget, IViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IViewPlugin)

private:
    Ui::MainForm *ui;
    IMainMenuModel *myModel;
    IMainMenuModel::MenuItem *rootMenuItem;
    PluginInfo *pluginInfo;

    QGraphicsScene *scene;
    QList<MenuItemGraphicsObject*> menuItems;
    QTimer *zoomAnimTimer;
    QPoint newCenter;
    float sceneScale;
    int scaleIter;

public:
    explicit MainMenuPluginView(QWidget *parent = 0);
    ~MainMenuPluginView();

    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;
public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

//    void AddModel(QObject *model) override;
    bool Open(IModelPlugin* model) override;
    bool Close() override;

    void SetRootMenuItem(IMainMenuModel::MenuItem *RootMenuItem);
    void AddSubitems(MenuItemGraphicsObject *ParentMenuItem, IMainMenuModel::MenuItem *ParentMenuItemStruct);
    void WipeAllItems();

private slots:
    void OpenChildPlugin(IMainMenuModel::MenuItem *menuItem, MetaInfo *viewMeta);
    void CloseMainMenu();

    void OnItemSelected(MenuItemGraphicsObject *menuItem);
    void ZoomAnimation();

signals:
    void OnOpen(QWidget *);
    void OnClose(PluginInfo *pointer);
    void OnClose();
    void OnItemSelected(IMainMenuModel::MenuItem *meta, MetaInfo *viewMeta);
};
//! \}
#endif // MAINMENUPLUGINVIEW_H
