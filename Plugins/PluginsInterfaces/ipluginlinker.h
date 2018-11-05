#ifndef IPLUGINLINKER_H
#define IPLUGINLINKER_H

#include <QtCore>

#include "../../Application/icoreplugin.h"

//! defgroup PluginLinker
//!     ingroup MainMenuPlugin_rel_m
//! defgroup PluginLinker_int Interface
//!     ingroup PluginLinker
//! defgroup PluginLinker_imp Implementation
//!     ingroup PluginLinker

//! addtogroup PluginLinker_int
//! {
class IPluginLinker
{
public:
    class ILinkerItem
    {
        const QString &getName();
        const QList<QString> &getReferenceNamesList();
        bool load();
        bool unload();

    signals:
        void onOpened(ILinkerItem *openedByItem);
        void onClosed(ILinkerItem *closedByItem);

    protected:
        virtual ~ILinkerItem() {}
    };

    virtual bool addCorePlugin(QWeakPointer<IPluginHandler> pluginHandler) = 0;
    virtual bool addNewPlugin(QWeakPointer<IPluginHandler> pluginHandler) = 0;
    virtual bool setupLinks() = 0;

    virtual const QWeakPointer<ILinkerItem> getCorePlugin() = 0;
    virtual const QMap<QString, QWeakPointer<ILinkerItem> > getClildPluginsMap() = 0;
    virtual const QMap<QString, QWeakPointer<ILinkerItem> > getAllPluginsMap() = 0;

protected:
    virtual ~IPluginLinker() {}
};
//! }
Q_DECLARE_INTERFACE(IPluginLinker, "IPluginLinker")
#endif // IPLUGINLINKER_H
