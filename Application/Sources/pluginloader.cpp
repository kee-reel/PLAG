#include "pluginloader.h"

#ifndef IS_CLI_APP
#include <QMessageBox>
#include <QDesktopServices>
#include <utility>
#endif

#include "pluginhandler.h"

const auto PLUGINS_DIR_NAME = QStringLiteral("Plugins");

PluginLoader::PluginLoader(QWidget *parentWidget) :
	m_parentWidget(parentWidget),
	m_pluginsPath(QStringLiteral("%1/%2/").arg(QDir::currentPath()).arg(PLUGINS_DIR_NAME)),
	m_pluginUidGeneratorCounter(1),
	m_askUidGeneratorCounter(1),
	m_internalAskId(0)
{
	connect(this, SIGNAL(onUserAnswered(quint32, quint16)), SLOT(onAnswered(quint32, quint16)));
}

void PluginLoader::setup()
{
	if(initPlugins())
	{
		Q_EMIT readyToStart();
	}
	else
	{
		m_internalAskId = askUser(QString("No required plugins found in directory %1. Open wiki page with more information?")
		                .arg(m_pluginsPath.absolutePath()), {"Ok", "No, just leave"});

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
	qDebug() << "PluginLoader::setupPlugins: loading plugins by path:" << libsDir.absolutePath();
	QCoreApplication::addLibraryPath(m_pluginsPath.absolutePath());

	Q_FOREACH (QString file, libsDir.entryList(QDir::Files))
	{
		makePluginHandler(libsDir.absolutePath() + "/" + file);
	}

	qDebug() << "PluginLoader::setupPlugins:" << m_corePluginHandlers.count() << "core plugins found, trying to load.";

	for(const auto& plugin : m_corePluginHandlers)
	{
		if(!plugin->load())
		{
			qDebug() << "Can't load plguin:" << plugin->getFileName();
			continue;
		}

		auto instance = plugin->getInstance();
		auto* corePluginInstance = castToPlugin<ICore>(instance);
		if(!corePluginInstance)
		{
			qDebug() << "PluginLoader::setupPlugins:" << m_corePluginHandlers.count() << "core plugins found, trying to load.";
			plugin->unload();
			continue;
		}

		m_corePluginHandler = plugin;
		m_corePluginInstance.reset(new QPair<ICore*, quint32>(corePluginInstance, plugin->getUID()));
		break;
	}

	return !m_corePluginInstance.isNull();
}

void PluginLoader::onAnswered(quint32 askId, quint16 optionIndex)
{
	if(m_internalAskId != askId)
		return;
#ifndef IS_CLI_APP
	if(optionIndex == 0)
	{
        QDesktopServices::openUrl(QUrl(QStringLiteral("https://kee-reel.com/mass-ru"), QUrl::TolerantMode));
	}
#endif
	Q_EMIT startFailed();
}

void PluginLoader::start(QWeakPointer<IApplication> app)
{
	Q_ASSERT(!m_corePluginInstance.isNull());
	qDebug() << "PluginLoader::runCorePlugin: starting core plugin.";
	m_corePluginInstance->first->coreInit(m_corePluginInstance->second, this, std::move(app));
}

bool PluginLoader::stop()
{
	return m_corePluginInstance->first->coreFini();
}

void PluginLoader::userAnswered(int optionIndex)
{
	auto askId = m_askQueue.last().askId;
	m_askQueue.pop_back();
	emit onUserAnswered(askId, optionIndex);
	if(m_askQueue.empty())
	{
		m_userAsked = false;
	}
	else
	{
		auto&& lastAsk = m_askQueue.last();
		emit userAsked(lastAsk.question, lastAsk.options);
	}
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
	auto handler = PluginHandler::make(m_pluginUidGeneratorCounter, path);
	if(!handler.isNull())
	{
		++m_pluginUidGeneratorCounter;
		registerPlugin(handler);
	}
	return handler;
}

QStringList PluginLoader::getCommandLineArguments()
{
	return QCoreApplication::arguments();
}

quint32 PluginLoader::askUser(const QString& question, const QVariantList& options)
{
	++m_askUidGeneratorCounter;
	m_askQueue.push_front({m_askUidGeneratorCounter, question, options});
	if(!m_userAsked)
	{
		m_userAsked = true;
		emit userAsked(question, options);
	}
	return m_askUidGeneratorCounter;
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
