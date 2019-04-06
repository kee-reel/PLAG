#include "mainmenumodelplugin.h"

#include <QPluginLoader>

MainMenuModelPlugin::MainMenuModelPlugin() :
    PluginBase(nullptr),
    m_widgetStack(nullptr),
    m_uiManager(nullptr),
    m_parentWidget(nullptr)
{
}

MainMenuModelPlugin::~MainMenuModelPlugin()
{
}

void MainMenuModelPlugin::addPlugins(const QVector<QWeakPointer<IPluginHandler>> &pluginHandlers)
{
    for(auto &plugin : pluginHandlers)
    {
        m_pluginLinker->addNewPlugin(plugin);
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

void MainMenuModelPlugin::onAllReferencesSetStateChanged()
{
    if(m_isAllReferencesSet)
    {
        for(const auto &reference : m_referencesMap)
        {
            const auto &meta = reference->getPluginMetaInfo();
            if(meta.InterfaceName == "IUIMANAGER")
            {
                if(!m_uiManager)
                {
                    qDebug() << "MainMenuModelPlugin::onAllReferencesSetStateChanged: UIManger set";
                    m_uiManagerPlugin = reference;
                    m_uiManager = castPluginToInterface<IUIManager>(reference);
                }
            }
        }
    }
}

QWidget *MainMenuModelPlugin::getWidget()
{
    return m_parentWidget;
}

int MainMenuModelPlugin::getCorePluginUID()
{

}

QMap<int, QWeakPointer<IPluginLinker::ILinkerItem> > MainMenuModelPlugin::getPluginsMap()
{

}
