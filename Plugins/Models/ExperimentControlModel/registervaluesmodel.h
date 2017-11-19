#ifndef REGISTERVALUESMODEL_H
#define REGISTERVALUESMODEL_H

#include <QAbstractItemModel>
#include <QBitArray>
#include <QObject>

#include "iexperimentcontrolmodel.h"

class RegisterValuesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    RegisterValuesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

public slots:
    void AddRegisterPack(IExperimentControlModel::RegstersPack pack);
    void RemoveRegisterPack(int row);

signals:
    void updateViewport();

public:
    QList<IExperimentControlModel::RegstersPack> packs;
    int m_number;
    int m_address;

private:
    QString GetRegisterString(QModbusDataUnit::RegisterType type) const;
    QModbusDataUnit::RegisterType GetRegisterType(QString str) const;
    IExperimentControlModel::RegstersPack *FindExistedPack(IExperimentControlModel::RegstersPack pack);
};

#endif // REGISTERVALUESMODEL_H
