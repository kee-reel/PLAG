#ifndef ROOTINTERFACES_H
#define ROOTINTERFACES_H

class QObject;
class QWidget;
class QJsonObject;
//! \addtogroup MASS MASS
//! @{

//! \brief Interface for plugin RootModel.
//! \details This interface represents most significant plugin in whole system. If plugin implements this
//! interface it should take care of whole system plugins interactions.
//! When PluginLoader class loads plugins from directory it searchs the plugin which
//! inherits from IRootModelPlugin. If it find one - it will send all loaded plugins to it by using AddPlugin()
//! method.
class IRootModelPlugin
{
public:
    virtual ~IRootModelPlugin() {}
    //! \brief Recieve loaded plugin with it's meta data.
    //! \param instance Plugin instance.
    //! \param meta Plugin meta data.
    virtual void AddPlugin(QObject* instance, QJsonObject* meta) = 0;

    //! \brief Starts plugin work. Some kind of 'start' signal.
    //! \param parentWidget This will be parent widget for all widgets in app.
    virtual void Run(QWidget* parentWidget) = 0;
};
Q_DECLARE_INTERFACE(IRootModelPlugin, "IRootModelPlugin v0.1")
//! @}
#endif // ROOTINTERFACES_H
