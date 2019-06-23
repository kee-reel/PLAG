#ifndef IAPPLICATION_H
#define IAPPLICATION_H

#include <QtGlobal>
#include <QObject>

#include "ipluginhandler.h"

template <class T>
class QWeakPointer;
class QPluginLoader;
class QWidget;

//!  \defgroup MainApp MainApp
//!  \defgroup Plugins Plugins

//! \addtogroup MainApp ICorePlugin
//! \{

//! \brief Interface for plugin CorePlugin.
//! \details This interface represents most significant plugin in whole system. If plugin implements this
//! interface it should take care of whole system plugins interactions.
//! When PluginLoader class loads plugins from directory it searchs the plugin which
//! inherits from ICorePlugin. If it find one - it will send all loaded plugins to it by using AddPlugin()
//! method.
class IApplication
{
public:
    virtual QWidget* getParentWidget() = 0;

    virtual QWeakPointer<IPluginHandler> getCorePlugin() = 0;

    virtual QVector<QWeakPointer<IPluginHandler>> getPlugins() = 0;

    virtual QWeakPointer<IPluginHandler> makePluginHandler(QString path) = 0;
protected:
    virtual ~IApplication() {}
};
Q_DECLARE_INTERFACE(IApplication, "IApplication")
//! \}
#endif // IAPPLICATION_H

