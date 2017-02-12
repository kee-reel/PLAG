#include "parentwindow.h"

ParentWindow::ParentWindow(QWidget *parent) : QWidget(parent)
{
    pluginManager = new PluginManager(this);
    QScreen *screen = QApplication::screens().at(0);
    this->resize(screen->size().width(),
        screen->size().height());

    pluginManager->SetupPlugins();
}
