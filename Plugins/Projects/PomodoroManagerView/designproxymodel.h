#ifndef DESIGNPROXYMODEL_H
#define DESIGNPROXYMODEL_H

#include <QSize>
#include <QFont>
#include <QBrush>
#include <QDebug>
#include <QIdentityProxyModel>

class DesignProxyModel : public QIdentityProxyModel
{
public:
    DesignProxyModel(QAbstractItemModel *model, QVector<int> modelIndexesShown = QVector<int>());

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    // QAbstractItemModel interface
public:
    int columnCount(const QModelIndex &parent) const;

private:
    QVector<int> modelIndexesShown;
    int columnsCount;
};
#endif // DESIGNPROXYMODEL_H
