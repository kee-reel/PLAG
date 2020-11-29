# MASS - Multi-Application Support System

#### The main idea of this application is to build a whole application in modular way - all the application functionality is provided by composing different subsets of plugins, where each plugin should have responsibility over specific part of application functionality.
## How it works
1. When main application starts it loads all plugins from folder "/Application/Plugins".

2. Among all loaded plugins it searches plugin that inherits interface [ICore](/Application/icore.h). 
That's how it looks:
```cpp
class ICore
{
public:
    virtual void coreInit(QWeakPointer<IApplication> app) = 0;
    virtual bool coreFini() = 0;
protected:
	virtual ~ICore() = default;
};
```

3. If main application finds plugin with ICore interface - it will pass instance that inherits [IApplication](/Application/iapplication.h) interface:
```cpp
class IApplication
{
public:
	virtual QWidget* getParentWidget() = 0;
	virtual const QVector<IPluginHandlerPtr> &getPlugins() = 0;
	virtual IPluginHandlerPtr makePluginHandler(const QString &path) = 0;
protected:
	virtual ~IApplication() = default;
};
```
to coreInit() method of ICore plugin. 

4. IApplication responsible for creating and storing plugin handler instances that inherited from [IPluginHandler](/Application/ipluginhandler.h):
```cpp
class IPluginHandler
{
public:
	virtual bool load() = 0;
	virtual bool unload() = 0;
	virtual QString getLastError() = 0;
	virtual QObject *getInstance() = 0;
	virtual QWeakPointer<QJsonObject> getMeta() = 0;
    virtual quint32 getUID() = 0;

protected:
	virtual ~IPluginHandler() = default;
};
using IPluginHandlerPtr = QWeakPointer<IPluginHandler>;
```
Plugin handlers are used to manage plugins loading/unloading that could be called from plugins.

5. Everything else is implemented in plugins. 

## Development process
All plugins (including core plugin) contains in another repo: https://gitlab.com/c4rb0n_un1t/MASS-Plugins. It's divided from this repo because it's possible to use any plugins set developed by you or any other developer.

If you just want quick start - run:
```bash
git clone https://gitlab.com/c4rb0n_un1t/MASS.git
cd MASS
git clone https://gitlab.com/c4rb0n_un1t/MASS-Plugins.git
cd MASS-Plugins/Projects
git clone https://gitlab.com/c4rb0n_un1t/mass-common-plugins.git
git clone https://gitlab.com/c4rb0n_un1t/mass-pim-plugins.git
```
It will download all needed repos. How to run the project you could read in https://gitlab.com/c4rb0n_un1t/MASS-Plugins README.