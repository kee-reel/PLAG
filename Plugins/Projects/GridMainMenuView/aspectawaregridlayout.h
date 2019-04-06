#ifndef ASPECTAWAREGRIDLAYOUT_H
#define ASPECTAWAREGRIDLAYOUT_H

#include <QWidget>
#include <QGridLayout>

class AspectAwareGridLayout : public QGridLayout
{
    Q_OBJECT
public:
    explicit AspectAwareGridLayout(QWidget *parent = 0);

signals:

public slots:

    // QLayoutItem interface
public:
    int heightForWidth(int) const override;
    bool hasHeightForWidth() const override;
};

#endif // ASPECTAWAREGRIDLAYOUT_H
