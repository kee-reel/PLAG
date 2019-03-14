#ifndef MAINMENUMODULE_H
#define MAINMENUMODULE_H

#include <QWidget>
#include <QDebug>
#include <QMap>
#include <QApplication>
#include <QJsonObject>

#include "../../PluginsCommon/plugin_base.h"
#include "../../../Application/icoreplugin.h"
#include "../../PluginsInterfaces/ipluginlinker.h"
#include "../../PluginsInterfaces/iuimanager.h"

#include "pluginlinker.h"
#include "widgetstack.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class MainMenuModelPlugin : public PluginBase, public ICorePlugin, public IPluginLinker
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        ICorePlugin
        IPluginLinker
    )

public:
    MainMenuModelPlugin();
    virtual ~MainMenuModelPlugin() override;

    // IRootModelPlugin interface
public:
    virtual void addPlugins(const QVector<QWeakPointer<IPluginHandler>> &pluginHandlers) override;
    virtual void start(QWeakPointer<IPluginHandler> selfHandler, QWidget *parentWidget) override;

    // PluginBase interface
protected:
    virtual void onAllReferencesSetStateChanged() override;

    // IPlugin interface
public:
    virtual QWidget *getWidget() override;

    // IPluginLinker interface
public:
    virtual int getCorePluginUID() override;
    virtual QMap<int, QWeakPointer<ILinkerItem> > getPluginsMap() override;

private:
    Q_PROPERTY(IPluginLinker* pluginLinker MEMBER m_pluginLinker USER true)
    Q_PROPERTY(IUIManager* uiManager MEMBER m_uiManager USER true)

private:
    IPluginLinker* m_pluginLinker;
    IUIManager *m_uiManager;

    QWidget *m_parentWidget;

    QWeakPointer<IPluginHandler> m_selfHandler;

};
//! @}
#endif // MAINMENUMODULE_H
