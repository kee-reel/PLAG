#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include "../MainMenuModelPlugin/imainmenumodule.h"
#include "menuitem.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

    void SetRootMenuItem(IMainMenuPluginModel::MenuItem *RootMenuItem);
    void AddSubitems(MenuItemGraphicsObject *ParentMenuItem, IMainMenuPluginModel::MenuItem *ParentMenuItemStruct);
    void WipeAllItems();

signals:
    void OnItemSelected(IMainMenuPluginModel::MenuItem *meta, MetaInfo *viewMeta);
    void OnClose();

private:
    Ui::MainForm *ui;
    IMainMenuPluginModel::MenuItem *rootMenuItem;
    QGraphicsScene *scene;
    QList<MenuItemGraphicsObject*> menuItems;
};

#endif // MAINFORM_H
