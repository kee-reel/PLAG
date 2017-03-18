#ifndef X_H
#define X_H

#include <QObject>

class X : public QObject
{
    Q_OBJECT
public:
    explicit X(QObject *parent = 0);

signals:

public slots:
};

#endif // X_H