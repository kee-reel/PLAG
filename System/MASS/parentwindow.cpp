#include "parentwindow.h"

ParentWindow::ParentWindow(QWidget *parent) : QWidget(parent)
{
//    childsJoint = new QWidget(this);
    layout = new QVBoxLayout();
    this->setLayout(layout);
    setWindowIcon(QIcon("://Resources/Logo512.png"));

    // Headless window mode
//    Qt::WindowFlags flags = windowFlags();
//    flags |= Qt::FramelessWindowHint;
//    setWindowFlags(flags);

    pluginManager = new PluginLoader(this);
#ifdef Q_OS_ANDROID
    QScreen *screen = QApplication::primaryScreen();
    this->resize(screen->size().width(),
        screen->size().height());
#else
    QScreen *screen = QApplication::primaryScreen();
    this->resize(screen->size().width()/3,
        screen->size().height()/2);
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
