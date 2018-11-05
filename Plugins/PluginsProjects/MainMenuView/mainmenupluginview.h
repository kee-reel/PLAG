#ifndef MAINMENUPLUGINVIEW_H
#define MAINMENUPLUGINVIEW_H

#include <QLayout>
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include "../../PluginsInterfaces/imainmenumodule.h"
#include "../../PluginsCommon/plugin_base.h"

class MenuItemGraphicsObject;

//! \defgroup MainMenuPluginView
//!     \ingroup MainMenuPlugin_rel_v
//! \defgroup MainMenuPluginView_imp Implementation
//!     \ingroup MainMenuPluginView

//! \addtogroup MainMenuPluginView_imp
//! \{
class MainMenuPluginView : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin)
public:
    explicit MainMenuPluginView(QWidget *parent = nullptr);
    ~MainMenuPluginView();

    void SetRootMenuItem(IMainMenuModel::IMenuItem *RootMenuItem);
    void AddSubitems(MenuItemGraphicsObject *ParentMenuItem, IMainMenuModel::IMenuItem *ParentMenuItemStruct);
    void WipeAllItems();

private slots:
    void OpenChildPlugin(IMainMenuModel::IMenuItem *menuItem, MetaInfo *viewMeta);
    void CloseMainMenu();

    void OnItemSelected(MenuItemGraphicsObject *menuItem);
    void ZoomAnimation();

private:
    IMainMenuModel::IMenuItem *rootMenuItem;
    QGraphicsScene *scene;
    QList<MenuItemGraphicsObject *> menuItems;
    QTimer *zoomAnimTimer;
    QPoint newCenter;
    float sceneScale;
    int scaleIter;
};
//! \}
#endif // MAINMENUPLUGINVIEW_H
