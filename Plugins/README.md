## Plugin types
So, as it said on the main page:
> Each plugin should have responsibility over a [s](https://en.wikipedia.org/wiki/Single_responsibility_principle)ingle part of the functionality.

According to this - there are only 4 main plugin types:
- **Model** - business logic and communication with other plugins
- **View** - user interface
- **DataManager** - provides data structures which not related to data source (database, network, COM-port and etc.)
- **DataSource** - communicates with data source

All these plugin types cover a lot of all possible application functionality. Actually, there isn't exists some special mechanism of controlling what you're doing inside your plugin - plugin type just marks you as a provider of some specific kind of functionality for other plugins.

## Exsisting plugins
For better understanding here are presented existing plugins with their functionality:
- **MainMenuModel** - holds links to plugins which available in main menu
- **MainMenuView** - provides main menu UI 
- **TaskListModel** - holds information about user tasks
- **TaskListView** - shows user tasks in tree sturcture
- **PomodoroModel** - holds information about user projects and finished [pomodoros](https://en.wikipedia.org/wiki/Pomodoro_Technique)
- **PomodoroView** - allows user to run pomodoros for selected projects
- **TaskSketchModel** - holds user sketches
- **TaskSketchView** - allows user to draw sketches, save them and observe gallery of drawed sketches
- **AndroidNotificationsModel** - provides API for using specific Android features (notifications and toasts) and set alarm on Adroid devices
- **ExtendableDataBaseManager** - provides access to information in data base in abstract item models
- **CipherDataBaseSource** - provide access to [SQLite plugin](https://github.com/devbean/QtCipherSqlitePlugin)

## How to make my own plugin
### Step one - Create project
Use custom wizard for QtCreator ([it is here](https://github.com/CurunirCingar/MASS/tree/master/Docs/QtCreator%20wizard)).
Type your plugin name and select plugin type. You should choose project directory according to your plugin type in "/Plugins" folder.
### Step two - Interacting with other plugins
To interact with other plugins you should know two things about them:
1. Their interface
2. Their plugin type

#### Where to find them? In other plugins info
Every plugin has its own plugin meta info. Let's look at our's plugin meta:
```js
{
    "Type": "PluginModel",
    "Interface": "IMyCustomModel",
    "Name": "MyCustomModel",
    "RelatedPluginInterfaces": [
    ]
}
```
Fields "Type", "Interface" and "Name" already filled according with information that you've put on previous step.
Field "RelatedPluginInterfaces" stands for relations to other plugins. If you want to interact with some plugin - you should put it's interface here. Afterwards, the linker will give you pointers to requested plugins.

Let's imagine that you want to interact with some data manager plugin (maybe [this one](https://github.com/CurunirCingar/MASS/tree/master/Plugins/DataManagers/ExtendableDataManager)) and also want to exist in the main menu ([that one](https://github.com/CurunirCingar/MASS/tree/master/Plugins/Models/MainMenuModel)).

You need to look into their's own plugin meta and search for field "Type" and "Interface". So, desired interfaces are "IExtendableDataManager" with type "DATAMANAGERPLUGIN" and "IMainMenuModel" with type "COREPLUGIN". For using interface in your code you need to include a header file with a description of their interface (it contains in plugin folder "i*.h").

#### Where to put them? To your code and plugin info
Put interfaces names in your plugin info:
```js
{
    "Type": "PluginModel",
    "Interface": "IMyCustomModel",
    "Name": "MyCustomModel",
    "RelatedPluginInterfaces": [
        "IExtendableDataManager",
        "IMainMenuModel"
    ]
}
```

Ok, next go to your generated "\*.cpp" file and look for AddReferencePlugin() method - there are example at the top of method.
```cpp
void MyCustomModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    /* Select your reference plugin type case and get it. For example:
        case MODELPLUGIN:{
            myReferencedPlugin = qobject_cast<ISomePlugin*>(pluginInfo->Instance);
            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not ISomePlugin.";
                return;
            }
            qDebug() << "ISomePlugin succesfully set.";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;
    */

    switch(pluginInfo->Meta->Type){
    ...
    }
}
```

Your requested plugins will be given to this method so you need to catch them - use interfaces and types that you've found. Interface for **qobject_cast** operation and 
```cpp
...
    case COREPLUGIN:{
        mainMenuModel = qobject_cast<IMainMenuModel*>(pluginInfo->Instance);
        if(!mainMenuModel)
        {
            qDebug() << pluginInfo->Meta->Name << "is not IMainMenuModel.";
            return;
        }
        qDebug() << "IMainMenuModel succesfully set.";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
    } break;
    case DATAMANAGERPLUGIN:{
        extendableDataManager = qobject_cast<IExtendableDataManager*>(pluginInfo->Instance);
        if(!extendableDataManager)
        {
            qDebug() << pluginInfo->Meta->Name << "is not IExtendableDataManager.";
            return;
        }
        qDebug() << "IExtendableDataManager succesfully set.";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
    }break;
...
}
```

**Subtle moment:** in method AddReferencePlugin() only **you** get pointer to plugin - referenced plugins ("IMainMenuModel" and "IExtendableDataManager") doesn't know a thing about you. There are could be plugins that could be needed your pointer for proper work. For example - main menu plugin (IMainMenuModel) will show your plugin on the menu only if you'll add it as a reference via his AddReferencePlugin(). So, for existing in the main menu you should append:
```cpp
        ...
        qDebug() << "IExtendableDataManager succesfully set.";
        **mainMenuModel->AddReferencePlugin(this->pluginInfo);**
        ...
```

### Step three - Providing interface to others
As other plugins you also have an interface - it also generated with the wizard:
```cpp
class IMyCustomModel :
        public IModelPlugin
{
public:
    // Write your interface methods here
};
```
So, if you want to provide some functionality to system - go ahead :)

## How to build all
There are "plugins.pro" file in "/Plugins" folder - by using it you could build all plugins.
In "/Application" folder you could use "MASS.pro" file for build main application.
----
*P.S.:* Currently I'm working on this documentation - so if you have some questions: curunir@yandex.ru