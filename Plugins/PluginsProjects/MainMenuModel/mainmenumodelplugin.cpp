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
        m_pluginLinker.addNewPlugin(plugin);
    }
}

void MainMenuModelPlugin::start(QWeakPointer<IPluginHandler> selfHandler, QWidget *parentWidget)
{
    qDebug() << "MainMenuModelPlugin::start";
    m_selfHandler = selfHandler;
    m_parentWidget = parentWidget;

    if(!m_pluginLinker.addCorePlugin(m_selfHandler))
    {
        return;
    }

    m_pluginLinker.setupLinks();

    const auto &corePluginLinkerItem = m_pluginLinker.getCorePlugin();
    corePluginLinkerItem.data()->load();
    corePluginLinkerItem.data()->open(nullptr);

    if(!m_uiManager)
    {
        qDebug() << "MainMenuModelPlugin::start: UIManger not found creating default UIManager";
        m_widgetStack = new WidgetStack(parentWidget);
        m_uiManager = static_cast<IUIManager *>(m_widgetStack);
    }

    m_uiManager->init(corePluginLinkerItem);
    auto plugins = m_pluginLinker.getClildPluginsMap();
    for(const auto &plugin : plugins)
    {
        m_uiManager->addChildItem(plugin);
    }

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
