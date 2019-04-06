#include "rawimagedelegate.h"

RawImageDelegate::RawImageDelegate()
{

}

void RawImageDelegate::SetValue(QVariant value)
{
    image = value.value<QImage>();
    if(image.isNull())
    {
        qDebug() << "Cant get image";
        return;
    }
}

QVariant RawImageDelegate::GetValue()
{
    QByteArray array = GetRawData();
    return QVariant(array);
}

QWidget *RawImageDelegate::GetWidget()
{
    //return this;
}

QByteArray RawImageDelegate::GetRawData()
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    buffer.close();
    return ba;
}
