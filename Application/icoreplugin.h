#ifndef ICOREPLUGIN_H
#define ICOREPLUGIN_H

#include <QtGlobal>
#include <QObject>

#include "ipluginhandler.h"

template <class T>
class QWeakPointer;
class QPluginLoader;
class QWidget;
//! \addtogroup MASS MASS
//! @{

//! \brief Interface for plugin CorePlugin.
//! \details This interface represents most significant plugin in whole system. If plugin implements this
//! interface it should take care of whole system plugins interactions.
//! When PluginLoader class loads plugins from directory it searchs the plugin which
//! inherits from ICorePlugin. If it find one - it will send all loaded plugins to it by using AddPlugin()
//! method.
class ICorePlugin
{
public:
    //! \brief Recieve loaded plugin with it's meta data.
    //! \param Plugin instance.
    //! \param Plugin meta data.
    virtual void addPlugins(const QVector<QWeakPointer<IPluginHandler>> &pluginHandlers) = 0;

    //! \brief Starts plugin work. Some kind of 'start' signal.
    //! \param This will be parent widget for all widgets in app.
    virtual void start(QWeakPointer<IPluginHandler> selfHandler, QWidget *parentWidget) = 0;

    //! \brief Starts plugin work. Some kind of 'start' signal.
    //! \param This will be parent widget for all widgets in app.
    virtual bool close() = 0;
protected:
    virtual ~ICorePlugin() {}
};
Q_DECLARE_INTERFACE(ICorePlugin, "ICorePlugin")
//! @}
#endif // ICOREPLUGIN_H

