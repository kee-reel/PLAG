#ifndef TASKTREEMODEL_H
#define TASKTREEMODEL_H

#include <QAbstractItemModel>
#include <QDebug>

#include "../../System/TaskDBToolPlugin/itaskdbtoolplugin.h"
#include "treeitem.h"

class TaskTreeItemModel : public QAbstractItemModel
{
public:
    QString tableName;
    ITaskDataManagerPlugin* dataManager;

    TaskTreeItemModel(QString tableName, ITaskDataManagerPlugin* dataManager, QList<ITaskDataManagerPlugin::TaskInfo> &data, QObject *parent = 0);
    ~TaskTreeItemModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void setupModelData(const QStringList &lines, TreeItem *parent);
    TreeItem *rootItem;

    ITaskDataManagerPlugin::TaskInfo ConvertToManagerTaskInfo(TreeItem* item);
    void DeleteFromManagerRecursive(TreeItem *task);

//    bool AddTask(TreeItem *taskParent, TreeItem taskData);
//    bool EditTask(TreeItem *task, TreeItem taskData);
//    bool DeleteTask(TreeItem *task);
};

#endif // TASKTREEMODEL_H
