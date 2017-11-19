#ifndef REGISTERSPACKTABLEMODEL_H
#define REGISTERSPACKTABLEMODEL_H

#include <QAbstractItemModel>
#include <QBitArray>
#include <QObject>

#include "iexperimentcontrolmodel.h"

class RegistersPackTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    RegistersPackTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

public slots:
    void AddRegisterPack(IExperimentControlModel::RegstersPack pack);

signals:
    void updateViewport();

public:
    void SetActiveDeviceId(int deviceId);

private:
    QMap<int, QList<IExperimentControlModel::RegstersPack> > devicesPacks;
    QList<IExperimentControlModel::RegstersPack> *selectdPacks;
    QString GetRegisterString(QModbusDataUnit::RegisterType type) const;
    QModbusDataUnit::RegisterType GetRegisterType(QString str) const;
    IExperimentControlModel::RegstersPack *FindExistedPack(IExperimentControlModel::RegstersPack pack);

    // QAbstractItemModel interface
public:
    bool removeRows(int row, int count, const QModelIndex &parent) override;
};

#endif // REGISTERSPACKTABLEMODEL_H
