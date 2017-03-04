#ifndef TASKTREEMODEL_H
#define TASKTREEMODEL_H

#include <QAbstractItemModel>
#include <QVariant>
#include <QVector>
#include <QDebug>
#include <QSize>
#include <QFont>
#include <QBrush>

#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"
#include "treeitem.h"

class TaskTreeItemModel : public QAbstractItemModel
{
    typedef IExtendableDataBaseManagerPlugin::TreeItemInfo TreeItemInfo;

public:
    QString tableName;
    QString coreRelationName;
    IExtendableDataBaseManagerPlugin* dataManager;

    TaskTreeItemModel(QString tableName,
                      IExtendableDataBaseManagerPlugin* dataManager,
                      QObject *parent = 0);
    ~TaskTreeItemModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles);
    bool insertRow(int row, const QModelIndex &parent);
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    void setupModelData(const QStringList &lines, TreeItem *parent);
    TreeItem *rootItem;

    TreeItemInfo ConvertToManagerTaskInfo(TreeItem* item);
    void DeleteFromManagerRecursive(TreeItem *task);

    bool AddTask(TreeItem *taskParent, TreeItem &taskData);
    bool EditTask(TreeItem *task, TreeItem taskData);
//    bool DeleteTask(TreeItem *task);

};

#endif // TASKTREEMODEL_H
