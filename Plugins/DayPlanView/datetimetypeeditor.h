#ifndef DATETIMETYPEEDITOR_H
#define DATETIMETYPEEDITOR_H

#include <QWidget>
#include <QDateTimeEdit>
#include <QVariant>

class DateTimeTypeEditor : public QDateTimeEdit
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue)

public:
    explicit DateTimeTypeEditor(QWidget *parent = nullptr);
    QVariant value() const;
    void setValue(const QVariant value);

signals:

public slots:
};

#endif // DATETIMETYPEEDITOR_H
