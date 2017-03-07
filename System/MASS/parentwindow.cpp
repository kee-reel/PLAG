#include "parentwindow.h"

ParentWindow::ParentWindow(QWidget *parent) : QWidget(parent)
{
//    childsJoint = new QWidget(this);
    layout = new QVBoxLayout();
    this->setLayout(layout);

    pluginManager = new PluginLoader(this);
#ifdef Q_OS_ANDROID
    QScreen *screen = QApplication::primaryScreen();
    this->resize(screen->size().width(),
        screen->size().height());
#endif
    pluginManager->SetupPlugins();
}

ParentWindow::~ParentWindow()
{
    delete pluginManager;
    //delete childsJoint;
    delete layout;
}

void ParentWindow::resizeEvent(QResizeEvent *event)
{
    layout->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
}
