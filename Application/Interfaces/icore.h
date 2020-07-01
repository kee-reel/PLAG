#pragma once


#include "iapplication.h"

//!  \defgroup MainApp MainApp
//!  \defgroup Plugins Plugins

//! \addtogroup MainApp ICore
//! \{

//! \brief Interface for core plugin.
//! \details This interface represents most significant plugin in whole system. If plugin implements this
//! interface it should take care of whole system plugins interactions.
//! When PluginLoader class loads plugins from directory it searchs the plugin which
//! inherits from ICore. If it find one - it will send all loaded plugins to it by using AddPlugin()
//! method.
class ICore
{
public:
	//! \brief Starts plugin work. Some kind of 'start' signal.
	//! \param This will be parent widget for all widgets in app.
	virtual void coreInit(quint32 corePluginUID, QObject* appObject, QWeakPointer<IApplication> app) = 0;

	//! \brief Starts plugin work. Some kind of 'start' signal.
	//! \param This will be parent widget for all widgets in app.
	virtual bool coreFini() = 0;
protected:
	virtual ~ICore() = default;
};
Q_DECLARE_INTERFACE(ICore, "ICore/1.0")
//! \}


