#ifndef IAPPLICATION_H
#define IAPPLICATION_H

#include <QtGlobal>
#include <QObject>

#include "ipluginhandler.h"

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
	
	virtual const QVector<IPluginHandlerPtr> &getPlugins() = 0;
	
	virtual IPluginHandlerPtr makePluginHandler(const QString &path) = 0;
};
Q_DECLARE_INTERFACE(IApplication, "IApplication/1.0")
//! \}
#endif // IAPPLICATION_H
