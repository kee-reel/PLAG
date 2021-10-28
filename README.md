# PLAG - PLugins AGgregator

#### Main idea: an application where __all__ features are implemented in plugins.

#### Analogy: it's like applications in OS, but plugins in application.

> This project made with C++/Qt for Linux, Windows, MacOS, Android and iOS.
> Once you've made a plugin, you can use it for all these platforms.

## How it works

1. When main application starts it loads all plugins from folder "/Application/Plugins".

2. Among all loaded plugins it searches plugin that inherits interface [ICore](/Application/Interfaces/icore.h). 

3. If main application finds plugin with ICore interface - it will:

* Load this plugin
* Pass an object that inherits [IApplication](/Application/Interfaces/iapplication.h) interface into this plugin

> IApplication represents main application and provides method for loading new plugins (other than ICore plugin)

4. ICore plugin will load remaining pluings and aggreate them into working application.

## Development process

Every plugin is stored in separate repository.

You can implement your own ICore plugin and whole framework of plugins that it will work with.

Or you can use existing plugins framework. You can read about it here: [gitlab.com/kee-reel/PLAGins](https://gitlab.com/kee-reel/PLAGins).

## Participation in development

Contact me if you're interested at: [telegram](https://t.me/kee_reel) or c4rb0n_unit@protonmail.com
