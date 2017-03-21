#ifndef TASKTREEMODEL_H
#define TASKTREEMODEL_H

#include <QAbstractItemModel>
#include <QVariant>
#include <QVector>
#include <QDebug>
#include <QMimeData>
#include <QDataStream>
#include <QMap>
#include <QApplication>

#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"
#include "treeitem.h"

class TaskTreeItemModel : public QAbstractItemModel
{
    typedef IExtendableDataBaseManagerPlugin::ManagerItemInfo ManagerItemInfo;

public:
    QString tableName;
    QString coreRelationName;
    IExtendableDataBaseManagerPlugin* dataManager;

    TaskTreeItemModel(QString tableName, IExtendableDataBaseManagerPlugin* dataManager, QObject *parent = 0);
    ~TaskTreeItemModel();
    void LoadData();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

private:
    int nameIndex;
    int parentIndex;
    int positionIndex;

    TreeItem defaultTask;
    TreeItem *rootItem;

    TreeItem *AddTask(int row, TreeItem *taskParent, TreeItem *taskData = NULL);
    bool EditTask(TreeItem *task, int column, QVariant dataField);
    bool UpdateTaskPositions(TreeItem *parent, int from);
    bool DeleteTask(TreeItem *task);
    void DeleteFromManagerRecursive(TreeItem *task);
    ManagerItemInfo ConvertToManagerTaskInfo(TreeItem* item);
};

#endif // TASKTREEMODEL_H
