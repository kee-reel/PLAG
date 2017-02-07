#include "parentwindow.h"

ParentWindow::ParentWindow(QWidget *parent) : QWidget(parent)
{
    resize(400, 400);

    pluginManager = new PluginManager(this);
    pluginManager->SetupPlugins();
}
