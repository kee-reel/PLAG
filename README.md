# MASS - Multiple Application Support System
Written with Qt framework.

## Main idea
It allows you to build whole your system from plugins. Each plugin holds responsibility only for determined set of functionality. There only 4 main types of plugins:
- **Model** - buisness logic and communication with other plugins
- **View** - user interface
- **DataManager** - provides data structures which not relate from source (database, network, COM-port and etc.)
- **DataSource** - communicates with data source

## Exsisting plugins
- **MainMenuModel** - holds links to plugins which available in main menu
- **MainMenuView** - provides main menu UI 
- **TaskListModel** - holds information about user tasks
- **TaskListView** - shows user tasks in tree sturcture
- **PomodoroModel** - holds information about user projects and finished [pomodoros](https://en.wikipedia.org/wiki/Pomodoro_Technique)
- **PomodoroView** - allows user to run pomodoros for selected projects
- **TaskSketchModel** - holds user sketches
- **TaskSketchView** - allows user to draw sketches, save them and observe gallery of drawed sketches
- **AndroidNotificationsModel** - provides API for using specific Android features (notifications and toasts) and set alarm
- **ExtendableDataBaseManager** - provides access to information in data base in abstract item models
- **CipherDataBaseSource** - provide access to [SQLite plugin](https://github.com/devbean/QtCipherSqlitePlugin)

If you interested in idea of crossplatform application which unlimitedly extendable and have some ideas or suggestions, please send me a message: *curunir@yandex.ru*. I've really need your help in bringing this project to life.
**Thank you.**
