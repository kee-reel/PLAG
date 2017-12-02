TEMPLATE = subdirs

SUBDIRS += \
    DataManagers/ExtendableDataManager/ExtendableDataManager.pro \
    DataManagers/ModbusDeviceDataManager/ModbusDeviceDataManager.pro \
    DataSources/COMPortDataSource/COMPortDataSource.pro \
    DataSources/DataBaseSource/DataBaseSource.pro \
    Models/DayPlanModel/DayPlanModel.pro \
    Models/ExperimentControlModel/ExperimentControlModel.pro \
    Models/MainMenuModel/MainMenuModelPlugin.pro \
#    Models/NeuralNetworkModel/NeuralNetworkModel.pro \
    Models/NotificationMangerModel/NotificationMangerModel.pro \
    Models/PomodoroModel/PomodoroModel.pro \
    Models/TaskListModel/TaskListModel.pro \
    Models/TaskSketchModel/TaskSketchModel.pro \
#    Views/ARNeuralNetworkView/ARNeuralNetworkView.pro \
    Views/DayPlanView/DayPlanView.pro \
    Views/ExperimentControlView/ExperimentControlView.pro \
    Views/GridMainMenuView/GridMainMenuView.pro \
    Views/MainMenuView/MainMenuViewPlugin.pro \
#    Views/PerceptronNeuralNetworkView/PerceptronNeuralNetworkView.pro \
    Views/PomodoroView/PomodoroView.pro \
    Views/TaskListView/TasksListView.pro \
    Views/TaskSketchView/TaskSketchView.pro
