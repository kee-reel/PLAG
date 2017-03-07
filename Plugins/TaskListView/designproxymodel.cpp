#include "designproxymodel.h"

DesignProxyModel::DesignProxyModel(QAbstractItemModel *model)
{
    setSourceModel(model);
}

QVariant DesignProxyModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::SizeHintRole:
        return QSize(0, 50);
        break;
    case Qt::FontRole:
        return QFont("Segoe UI", 20, QFont::Bold);
        break;
    case Qt::BackgroundRole:
        return QBrush(QColor(100 + index.row()*10, 180, 180));
        break;
    default:
        return QIdentityProxyModel::data(index, role);
        break;
    }
}

QVariant DesignProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role) {
    case Qt::SizeHintRole:
        return QSize(0, 30);
        break;
    case Qt::FontRole:
        return QFont("Segoe UI", 14, QFont::Bold);
        break;
    case Qt::BackgroundRole:
        return QBrush(QColor(120 + section*10, 180, 180));
        break;
    default:
        return QIdentityProxyModel::headerData(section, orientation, role);
        break;
    }
}
