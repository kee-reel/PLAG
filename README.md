# MASS - Multiple Application Support System

#### The main idea of this application is to build a whole application in a modular way - all the application functionality is provided by composing different subsets of plugins, where each plugin should have responsibility over a [s](https://en.wikipedia.org/wiki/Single_responsibility_principle)ingle part of the functionality.
## How it works
Main application which are storing in folder ["/Application"](/Application) loads all plugins from folder ["/Application/Plugins"](/Application/Plugins).

Among all loaded plugins it searches the one, which inherits interface [ICorePlugin](https://github.com/CurunirCingar/MASS/blob/master/Application/rootinterface.h). If it finds one - it will send all other loaded plugins to it by using AddPlugin(). After all main application calls Run() method.

If plugin implements [ICorePlugin](https://github.com/CurunirCingar/MASS/blob/master/Application/rootinterface.h) interface it should take care of whole system plugins interactions. Here's it's code ([doc](https://curunircingar.github.io/MASS/class_i_core_plugin.html)):
```cpp
class ICorePlugin
{
public:
    virtual void addPlugins(const QVector<QWeakPointer<IPluginHandler>> &pluginHandlers) = 0;
    virtual void start(QWeakPointer<IPluginHandler> selfHandler, QWidget *parentWidget) = 0;
    virtual bool close() = 0;
protected:
    virtual ~ICorePlugin() {}
};
```

So, that's all that designed in a non-modular way - everything else contains in plugins :)

## Plugins implementation aspect
All plugins are loaded using [QPluginLoader](http://doc.qt.io/qt-5/qpluginloader.html) and should contain [plugin specific macroses](http://doc.qt.io/qt-5/plugins-howto.html).
If you're using QtCreator then you can use custom wizard for generating solutions for new plugins - [link](https://github.com/CurunirCingar/MASS/tree/master/Docs/QtCreator%20wizard).

## Development
All plugins (including core plugin) contains in ["/Plugins"](/Plugins). Description of the plugins-related theme is separated from the current page because theoretically, you could make your own implementation of core plugin.

So if you want to read more about the already implemented architecture of these plugins and how all this stuff works - jump [here](/Plugins).
