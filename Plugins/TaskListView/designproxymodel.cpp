#include "designproxymodel.h"

DesignProxyModel::DesignProxyModel(QAbstractItemModel *model)
{
    setSourceModel(model);
}

QVariant DesignProxyModel::data(const QModelIndex &index, int role) const
{
    // TODO: Proxy index
    QModelIndex proxyIndex = index;//createIndex(index.row(), 1, index.internalPointer());
    switch (role) {
    case Qt::SizeHintRole:
        return QSize(0, 50);
        break;
    case Qt::FontRole:
        return QFont("Segoe UI", 20, QFont::Bold);
        break;
    case Qt::BackgroundRole: {
        int color = 100 + index.row()*10;
        color = (color >= 255) ? 255 : color;
        return QBrush(QColor(color, 180, 180));
        }
        break;
    default:
        return QIdentityProxyModel::data(proxyIndex, role);
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
