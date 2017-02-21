#include "parentwindow.h"

ParentWindow::ParentWindow(QWidget *parent) : QWidget(parent)
{
    qDebug() << "!";
    pluginManager = new PluginManager(this);
    QScreen *screen = QApplication::screens().at(0);
    qDebug() << "!";
#ifdef Q_OS_ANDROID
    this->resize(screen->size().width(),
        screen->size().height());
#endif
    pluginManager->SetupPlugins();
}
