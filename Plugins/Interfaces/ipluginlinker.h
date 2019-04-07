#ifndef IPLUGINLINKER_H
#define IPLUGINLINKER_H

#include <QtCore>


#include "../../Application/ipluginhandler.h"
#include "../Common/iplugin.h"

//!  \defgroup PluginLinker PluginLinker
//!      \ingroup Plugins
//!  \defgroup PluginLinker_int Interface
//!      \ingroup PluginLinker
//!  \defgroup PluginLinker_imp Implementation
//!      \ingroup PluginLinker
//!  \defgroup PluginLinker_dep Dependent plugins
//!      \ingroup PluginLinker

//!  \addtogroup PluginLinker_int
//!  \{
class IPluginLinker
{
public:
    class ILinkerItem
    {
    public:
        virtual bool isLoaded() const = 0;
        virtual bool isOpened() const = 0;
        virtual MetaInfo getMeta() const = 0;
        virtual int getPluginUID() const = 0;

        virtual QWidget *getWidget() const = 0;
        virtual const QObject *getObject() const = 0;

        virtual QMap<int, QWeakPointer<ILinkerItem>> getReferences() = 0;
        virtual QMap<int, QWeakPointer<ILinkerItem>> getReferents() = 0;

        virtual bool open() = 0;
        virtual bool close() = 0;

    signals:
        void onOpened(int itemId);
        void onClosed(int itemId);
        void onConnectionsChanged(int itemId);
    };

    virtual bool addCorePlugin(QWeakPointer<IPluginHandler> pluginHandler) = 0;
    virtual bool addPlugin(QWeakPointer<IPluginHandler> pluginHandler) = 0;
    virtual bool setupLinks() = 0;

    virtual int getCorePluginUID() = 0;
    virtual QMap<int, QWeakPointer<ILinkerItem> > getPluginsMap() = 0;

signals:
    void onLinkageFinished();
};
//!  \}
Q_DECLARE_INTERFACE(IPluginLinker, "IPluginLinker")
#endif // IPLUGINLINKER_H
