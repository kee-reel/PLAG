#ifndef MAINMENUMODULE_H
#define MAINMENUMODULE_H

#include <QWidget>
#include <QDebug>
#include <QMap>
#include <QApplication>
#include <QJsonObject>

#include "../../PluginsCommon/plugin_base.h"
#include "../../../Application/icoreplugin.h"

#include "pluginlinker.h"
#include "widgetstack.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class MainMenuModelPlugin : public PluginBase, ICorePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(ICorePlugin)

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

private:
    WidgetStack *m_widgetStack;

    IPlugin *m_uiManagerPlugin;
    IUIManager *m_uiManager;
    QWidget *m_parentWidget;

    QWeakPointer<IPluginHandler> m_selfHandler;
    PluginLinker m_pluginLinker;

};
//! @}
#endif // MAINMENUMODULE_H
