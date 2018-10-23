#ifndef WIDGETSTACK_H
#define WIDGETSTACK_H

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QWidget>
#include <QList>
#include <QLayout>

class WidgetStack : public QObject
{
    Q_OBJECT
public:
    explicit WidgetStack(QWidget *parent = 0);

public slots:
    void Pop();
    void Push(QWidget *widget);
    int Count();
    QWidget *GetTop();

signals:
    void OnPop();

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QList<QWidget*> widgetStack;
};

#endif // WIDGETSTACK_H
