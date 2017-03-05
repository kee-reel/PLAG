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
    typedef IExtendableDataBaseManagerPlugin::ManagerItemInfo ManagerItemInfo;

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
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    int nameIndex;
    int parentIndex;
    int positionIndex;

    TreeItem defaultTask;

    void setupModelData(const QStringList &lines, TreeItem *parent);
    TreeItem *rootItem;

    ManagerItemInfo ConvertToManagerTaskInfo(TreeItem* item);
    void DeleteFromManagerRecursive(TreeItem *task);

    TreeItem *AddTask(TreeItem *taskParent, TreeItem *taskData = NULL);
    bool EditTask(TreeItem *task, int column, QVariant dataField);
    bool DeleteTask(TreeItem *task);

};

#endif // TASKTREEMODEL_H
