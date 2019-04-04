#include "designproxymodel.h"

DesignProxyModel::DesignProxyModel(QAbstractItemModel *model)
{
    setSourceModel(model);
    this->model = model;
}

QVariant DesignProxyModel::data(const QModelIndex &index, int role) const
{
    // TODO: Proxy index
    QModelIndex proxyIndex = index;//createIndex(index.row(), 1, index.internalPointer());
    switch (role) {
    case Qt::SizeHintRole:
#ifdef Q_OS_ANDROID
    return QSize(0, 80);
#else
    return QSize(0, 30);
#endif
        break;
    case Qt::FontRole:
#ifdef Q_OS_ANDROID
    return QFont("Segoe UI", 26, QFont::Bold);
#else
    return QFont("Segoe UI", 14, QFont::Bold);
#endif
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
    case Qt::UserRole:
        return model->headerData(section, orientation, role);
        break;
    default:
        return QIdentityProxyModel::headerData(section, orientation, role);
        break;
    }
}

QMap<int, QVariant> DesignProxyModel::itemData(const QModelIndex &index) const
{
    return model->itemData(index);
}

bool DesignProxyModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    return model->setItemData(index, roles);
}
