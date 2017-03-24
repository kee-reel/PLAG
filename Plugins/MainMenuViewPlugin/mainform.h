#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include "../MainMenuModelPlugin/imainmenumodule.h"

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
    void WipeAllItems();

private:
    Ui::MainForm *ui;
    IMainMenuPluginModel::MenuItem *rootMenuItem;
    QGraphicsScene *scene;
    QList<QGraphicsEllipseItem*> menuItems;
};

#endif // MAINFORM_H
