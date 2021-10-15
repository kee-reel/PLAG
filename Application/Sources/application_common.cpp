#include "application.h"

#include <QCoreApplication>

#ifdef Q_OS_ANDROID
#include "pluginloader_android.h"
#else
#include "pluginloader.h"
#endif

Application::Application() :
#ifdef IS_CLI_APP
	QObject()
#else
	QQuickWidget()
#endif
{
#ifdef IS_CLI_APP
	QWidget* parent = nullptr;
#else
	QWidget* parent = this;
#endif
#ifdef Q_OS_ANDROID
	m_pluginManager.reset(new PluginLoaderAndroid(this));
#else
	m_pluginManager.reset(new PluginLoader(parent));
#endif
	init();

	connect(m_pluginManager.data(), &PluginLoader::readyToStart, this, &Application::onReadyToStart, Qt::QueuedConnection);
	connect(m_pluginManager.data(), &PluginLoader::startFailed, this, &Application::onStartFailed, Qt::QueuedConnection);
	connect(m_pluginManager.data(), &PluginLoader::userAsked, this, &Application::onUserAsk);

#ifndef IS_CLI_APP
	setResizeMode(QQuickWidget::SizeRootObjectToView);
	setSource(QUrl("qrc:/Sources/Main.qml"));
	connect(rootObject(), SIGNAL(onOptionChosen(int)), this, SLOT(onOptionChosen(int)), Qt::QueuedConnection);
#endif
}

void Application::childEvent(QChildEvent* event)
{
#ifndef IS_CLI_APP
	if(event->added())
	{
		resizeChildren(size().width(), size().height());
	}
	QQuickWidget::childEvent(event);
#endif
}

void Application::onUserAsk(const QString& question, const QVariantList& options)
{
#ifndef IS_CLI_APP
	QMetaObject::invokeMethod(rootObject(), "askUser", Q_ARG(QVariant, question), Q_ARG(QVariant, options));
#endif
}

void Application::onOptionChosen(int index)
{
	m_pluginManager->userAnswered(index);
}

#ifndef IS_CLI_APP
void Application::resizeChildren(int w, int h)
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

void Application::resizeEvent(QResizeEvent* event)
{
	auto&& w = event->size().width();
	auto&& h = event->size().height();
	resizeChildren(w, h);
	QQuickWidget::resizeEvent(event);
}
#endif

void Application::start()
{
	m_pluginManager->setup();
}

void Application::onReadyToStart()
{
	m_pluginManager->start(m_pluginManager);
}

void Application::onStartFailed()
{
	QCoreApplication::quit();
}
