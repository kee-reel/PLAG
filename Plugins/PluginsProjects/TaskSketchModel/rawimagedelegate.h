#ifndef RAWIMAGEDELEGATE_H
#define RAWIMAGEDELEGATE_H
#include <QBuffer>
#include <QImage>
#include <QWidget>
#include <QImage>
#include <QVariant>
#include <QDebug>

#include "../../PluginsInterfaces/itasktreemodel.h"

class RawImageDelegate
{
public:
    RawImageDelegate();

    // ITaskRelationDelegate interface
public:
    void SetValue(QVariant value);
    QVariant GetValue();
    QWidget *GetWidget();

private:
    QByteArray GetRawData();
    QImage image;
};

#endif // RAWIMAGEDELEGATE_H
