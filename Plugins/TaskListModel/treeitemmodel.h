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

class TreeItemModel : public QAbstractItemModel
{
    typedef IExtendableDataBaseManagerPlugin::ManagerItemInfo ManagerItemInfo;

public:
    QString tableName;
    QString coreRelationName;
    IExtendableDataBaseManagerPlugin* dataManager;

    TreeItemModel(QString tableName, IExtendableDataBaseManagerPlugin* dataManager, QObject *parent = 0);
    ~TreeItemModel();
    void LoadData();
    bool AttachRelation(QMap<QString, QVariant::Type> relationStruct, QString relationName, QVector<QVariant> defaultData);
    void SetActiveRelation(QString relationName);

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool insertColumns(int column, int count, const QModelIndex &parent) override;
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

    QHash<int, TreeItem*> internalList;
    QString currentActiveChunkName;
    TreeItem defaultTask;
    TreeItem *rootItem;

    TreeItem *AddItem(int row, TreeItem *taskParent, TreeItem *taskData = NULL);
    bool EditItem(TreeItem *task, int column, QVariant dataField);
    bool UpdateItemsPosition(TreeItem *parent, int from);
    bool DeleteItem(TreeItem *task);
    void DeleteFromManagerRecursive(TreeItem *task);
    ManagerItemInfo ConvertToManagerItem(TreeItem* item);
};

#endif // TASKTREEMODEL_H
