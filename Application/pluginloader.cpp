#include "pluginloader.h"

#include <QMessageBox>
#include <QDesktopServices>
#include <utility>

#include "pluginhandler.h"

const auto PLUGINS_DIR_NAME = QStringLiteral("Plugins");

PluginLoader::PluginLoader(QWidget *parentWidget) :
	m_parentWidget(parentWidget),
	m_pluginsPath(QStringLiteral("%1/%2/").arg(QDir::currentPath()).arg(PLUGINS_DIR_NAME)),
	m_corePluginInstance(nullptr),
	m_uidGeneratorCounter(0)
{
}

void PluginLoader::setup()
{
	if(initPlugins())
	{
		Q_EMIT readyToStart();
	}
	else
	{
		int res = QMessageBox::question(m_parentWidget, QStringLiteral("No plugins"), 
										QStringLiteral("No required plugins found in directory %1. Open wiki page with more information?")
										.arg(m_pluginsPath.absolutePath()));
		if(res == QMessageBox::Yes)
		{
			QDesktopServices::openUrl(QUrl(QStringLiteral("https://gitlab.com/c4rb0n_un1t/MASS/wikis/home"), QUrl::TolerantMode));
		}
		Q_EMIT startFailed();
	}
}

void PluginLoader::registerPlugin(const QSharedPointer<PluginHandler>& handler)
{
	if(handler->isCorePlugin())
	{
		m_corePluginHandlers.append(handler);
	}
	m_pluginHandlers.append(handler);
	m_rawPluginHandlers.append(handler);
}

bool PluginLoader::initPlugins()
{
	QDir libsDir(m_pluginsPath);
	//	qDebug() << "PluginLoader::setupPlugins: loading plugins by path:" << libsDir.absolutePath();
	QApplication::addLibraryPath(m_pluginsPath.absolutePath());
	
	Q_FOREACH (QString file, libsDir.entryList(QDir::Files))
	{
		makePluginHandler(libsDir.absolutePath() + "/" + file);
	}
	
	//	qDebug() << "PluginLoader::setupPlugins:" << m_corePluginHandlers.count() << "core plugins found, trying to load.";
	
	for(const auto& plugin : qAsConst(m_corePluginHandlers))
	{
		if(!plugin.data()->load())
		{
			continue;
		}
		
		auto instance = plugin.data()->getInstance();
		auto* corePluginInstance = castToPlugin<ICore>(instance);
		if(!corePluginInstance)
		{
			//qDebug() << "PluginLoader::setupPlugins:" << m_corePluginHandlers.count() << "core plugins found, trying to load.";
			plugin.data()->unload();
			continue;
		}
		
		m_corePluginHandler = plugin;
		m_corePluginInstance = corePluginInstance;
		break;
	}
	
	return m_corePluginInstance != nullptr;
}

void PluginLoader::start(QWeakPointer<IApplication> app)
{
	Q_ASSERT(m_corePluginInstance);
	//	qDebug() << "PluginLoader::runCorePlugin: starting core plugin." << endl;
	m_corePluginInstance->coreInit(std::move(app));
}

bool PluginLoader::stop()
{
	return m_corePluginInstance->coreFini();
}

QWidget *PluginLoader::getParentWidget()
{
	return m_parentWidget;
}

const QVector<IPluginHandlerPtr> &PluginLoader::getPlugins()
{
	return m_rawPluginHandlers;
}

IPluginHandlerPtr PluginLoader::makePluginHandler(const QString &path)
{
	auto handler = PluginHandler::make(m_uidGeneratorCounter, path);
	if(!handler.isNull())
	{
		++m_uidGeneratorCounter;
		registerPlugin(handler);
	}
	return handler;
}

template <class Type>
Type *PluginLoader::castToPlugin(QObject *possiblePlugin)
{
	Type *plugin = qobject_cast<Type *>(possiblePlugin);
	
	if(!plugin)
	{
		qDebug() << "PluginLoader::castToPlugin: can't cast the plugin " << possiblePlugin->objectName() << ": wrong type.";
	}
	
	return plugin;
}
