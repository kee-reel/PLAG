#include "mainmenumodelplugin.h"

#include <QPluginLoader>

MainMenuModelPlugin::MainMenuModelPlugin() :
    PluginBase(nullptr),
    m_parentWidget(nullptr)
{
}

MainMenuModelPlugin::~MainMenuModelPlugin()
{
}

void MainMenuModelPlugin::addPlugins(const QVector<QWeakPointer<IPluginHandler>> &pluginHandlers)
{
    m_pluginHandlers = pluginHandlers;
    for(auto &plugin : m_pluginHandlers)
    {
        qDebug() << plugin.data()->getMeta().keys();
        QJsonObject metaInfo = plugin.data()->getMeta().value("MetaData").toObject();
        qDebug() << metaInfo.keys();
        if(metaInfo.find("IsPluginLinker") != metaInfo.end())
        {
            qDebug() << "Found linker!";
            QObject* instance = plugin.data()->getInstance();
            m_pluginLinker = qobject_cast<IPluginLinker*>(instance);
        }
    }

    for (auto &plugin : m_pluginHandlers)
    {
        m_pluginLinker->addPlugin(plugin);
    }
}

void MainMenuModelPlugin::start(QWeakPointer<IPluginHandler> selfHandler, QWidget *parentWidget)
{
    m_selfHandler = selfHandler;
    m_parentWidget = parentWidget;

    if(!m_pluginLinker->addCorePlugin(m_selfHandler))
    {
        return;
    }

    m_pluginLinker->setupLinks();

    const auto &corePluginLinkerItem = m_pluginLinker->getCorePlugin();
    corePluginLinkerItem.data()->load();
    corePluginLinkerItem.data()->open(nullptr);

    if(!m_uiManager)
    {
        qDebug() << "MainMenuModelPlugin::start: UIManger not found creating default UIManager";
        m_widgetStack.reset(new WidgetStack(parentWidget));
        m_uiManager = m_widgetStack.get();
    }

    m_uiManager->init(QWeakPointer<IUIManager::IUIElement>());// corePluginLinkerItem);
    auto plugins = m_pluginLinker->getClildPluginsMap();
    QStringList pluginNames;

    for(const auto &plugin : plugins)
    {
        pluginNames.append(plugin.data()->getPluginDescriptionName());
        m_uiManager->addChildItem(plugin);
    }

    qDebug() << "MainMenuModelPlugin::start: available plugins:";
    for(const auto &name : pluginNames)
    {
        qDebug() << name;
    }
    qDebug() << endl;

    m_uiManagerPlugin->open(this);
}

QWidget *MainMenuModelPlugin::getWidget()
{
    return m_parentWidget;
}

void MainMenuModelPlugin::onAllReferencesSetStateChanged()
{
    auto iter = m_referencesMap.begin();
    while(iter != m_referencesMap.end())
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IPluginLinker", Qt::CaseInsensitive))
        {
            qDebug() << "Linker set~";
            m_pluginLinker = qobject_cast<IPluginLinker*>(plugin->getObject());
        }
        else if(!QString::compare(interfaceName, "IUIManager", Qt::CaseInsensitive))
        {
            qDebug() << "UIMAnager set~";
            m_uiManager = qobject_cast<IUIManager*>(plugin->getObject());
        }
    }
}
