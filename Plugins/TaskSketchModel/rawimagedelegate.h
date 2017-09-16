#ifndef RAWIMAGEDELEGATE_H
#define RAWIMAGEDELEGATE_H
#include <QBuffer>
#include <QImage>
#include <QWidget>
#include <QImage>
#include <QVariant>
#include <QDebug>

#include "../TaskListModel/itasktreemodel.h"

class RawImageDelegate : ITaskTreeModel::ITaskRelationDelegate
{
public:
    RawImageDelegate();

    // ITaskRelationDelegate interface
public:
    void SetValue(QVariant value) override;
    QVariant GetValue() override;
    QWidget *GetWidget() override;

private:
    QByteArray GetRawData();
    QImage image;
};

#endif // RAWIMAGEDELEGATE_H
