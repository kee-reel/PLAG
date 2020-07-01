#include "parentwindow.h"

#include <QApplication>

#ifdef Q_OS_ANDROID
#include "pluginloader_android.h"
#else
#include "pluginloader.h"
#endif

ParentWindow::ParentWindow(QWidget *parent) :
	QQuickWidget(parent)
{
#ifdef Q_OS_ANDROID
	m_pluginManager.reset(new PluginLoaderAndroid(this));
#else
	m_pluginManager.reset(new PluginLoader(this));
#endif
	init();

	connect(m_pluginManager.data(), &PluginLoader::readyToStart, this, &ParentWindow::onReadyToStart, Qt::QueuedConnection);
	connect(m_pluginManager.data(), &PluginLoader::startFailed, this, &ParentWindow::onStartFailed, Qt::QueuedConnection);
	connect(m_pluginManager.data(), &PluginLoader::userAsked, this, &ParentWindow::onUserAsk);

	setResizeMode(QQuickWidget::SizeRootObjectToView);
	setSource(QUrl("qrc:/Sources/Main.qml"));
	connect(rootObject(), SIGNAL(onOptionChosen(int)), this, SLOT(onOptionChosen(int)), Qt::QueuedConnection);
}

void ParentWindow::childEvent(QChildEvent* event)
{
	if(event->added())
	{
		resizeChildren(size().width(), size().height());
	}
	QQuickWidget::childEvent(event);
}

void ParentWindow::onUserAsk(const QString& question, const QVariantList& options)
{
	QMetaObject::invokeMethod(rootObject(), "askUser", Q_ARG(QVariant, question), Q_ARG(QVariant, options));
}

void ParentWindow::onOptionChosen(int index)
{
	m_pluginManager->userAnswered(index);
}

void ParentWindow::resizeChildren(int w, int h)
{
	for(auto& child : children())
	{
		auto widget = qobject_cast<QWidget*>(child);
		if(widget)
		{
			widget->setGeometry(0, 0, w, h);
		}
	}
}

void ParentWindow::resizeEvent(QResizeEvent* event)
{
	auto&& w = event->size().width();
	auto&& h = event->size().height();
	resizeChildren(w, h);
	QQuickWidget::resizeEvent(event);
}

void ParentWindow::start()
{
	m_pluginManager->setup();
}

void ParentWindow::onReadyToStart()
{
	m_pluginManager->start(m_pluginManager);
}

void ParentWindow::onStartFailed()
{
	QApplication::quit();
}
