#include "parentwindow.h"

#include <QApplication>

#ifdef Q_OS_ANDROID
#include "pluginloader_android.h"
#else
#include "pluginloader.h"
#endif

ParentWindow::ParentWindow(QWidget *parent) :
	QWidget(parent)
	
{
#ifdef Q_OS_ANDROID
	m_pluginManager.reset(new PluginLoaderAndroid(this));
#else
	m_pluginManager.reset(new PluginLoader(this));
#endif
	
	connect(m_pluginManager.data(), &PluginLoader::readyToStart, this, &ParentWindow::onReadyToStart, Qt::QueuedConnection);
	connect(m_pluginManager.data(), &PluginLoader::startFailed, this, &ParentWindow::onStartFailed, Qt::QueuedConnection);

	init();
}

void ParentWindow::start()
{
	m_pluginManager->setup();
}

void ParentWindow::resizeEvent(QResizeEvent *event)
{
	layout->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
}

void ParentWindow::onReadyToStart()
{
	m_pluginManager->start(m_pluginManager);
}

void ParentWindow::onStartFailed()
{
	QApplication::quit();
}
