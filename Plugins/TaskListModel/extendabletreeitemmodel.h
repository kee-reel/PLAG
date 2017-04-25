#ifndef EXTENDABLETREEITEMMODEL_H
#define EXTENDABLETREEITEMMODEL_H

#include <QAbstractItemModel>
#include <QVariant>
#include <QVector>
#include <QDebug>
#include <QMimeData>
#include <QDataStream>
#include <QMap>
#include <QApplication>

#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"
#include "item.h"

class ExtendableTreeItemModel : public QAbstractItemModel
{
    typedef IExtendableDataBaseManagerPlugin::ManagerItemInfo ManagerItemInfo;
public:
    QString tableName;
    QString coreRelationName;
    IExtendableDataBaseManagerPlugin* dataManager;

    ExtendableTreeItemModel(QString tableName, IExtendableDataBaseManagerPlugin* dataManager, QObject *parent = 0);
    ~ExtendableTreeItemModel();
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
    int parentIndex;
    int positionIndex;

    QHash<int, Item*> internalList;
    QString currentActiveChunkName;
    Item defaultTask;
    Item *rootItem;

    Item *AddItem(int row, Item *taskParent, Item *taskData = NULL);
    bool EditItem(Item *task, int column, QVariant dataField);
    bool UpdateItemsPosition(Item *parent, int from);
    bool DeleteItem(Item *task);
    void DeleteFromManagerRecursive(Item *task);
    ManagerItemInfo ConvertToManagerItem(Item* item);
};

#endif // TASKTREEMODEL_H
