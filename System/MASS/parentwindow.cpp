#include "parentwindow.h"

ParentWindow::ParentWindow(QWidget *parent) : QWidget(parent)
{
    pluginManager = new PluginLoader(this);
#ifdef Q_OS_ANDROID
    QScreen *screen = QApplication::primaryScreen();
    this->resize(screen->size().width(),
        screen->size().height());
#endif
    pluginManager->SetupPlugins();
}
