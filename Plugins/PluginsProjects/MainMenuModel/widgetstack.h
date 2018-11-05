#ifndef WIDGETSTACK_H
#define WIDGETSTACK_H

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QWidget>
#include <QList>
#include <QLayout>

#include "../../PluginsInterfaces/iuimanager.h"

class WidgetStack : public QObject, public IUIManager
{
    Q_OBJECT
public:
    explicit WidgetStack(QWidget *parent = nullptr);
    virtual ~WidgetStack() override {}

public slots:
    void pop();
    void push(QWidget *widget);
    int count();
    QWidget *getTop();

signals:
    void onPop();

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;

    // IUIManager interface
public:
    virtual bool init(QWeakPointer<IUIElement> rootElement) override;
    virtual bool fini() override;
    virtual bool addChildItem(QWeakPointer<IUIElement> element) override;
    virtual bool removeChildItem(QWeakPointer<IUIElement> element) override;

    const QWeakPointer<IUIElement> getRootElement();
    const QVector<QWeakPointer<IUIElement> > getChildElements();

private:
    bool validateElement(QWeakPointer<IUIElement> element) const;
    const QWeakPointer<IUIElement> &getElementById(int elementId) const;

private slots:
    void onElementOpened(int elementId);
    void onElementClosed(int elementId);
    void onElementConnectionChanged(int elementId);

private:
    QMap<int, QWeakPointer<IUIElement>> m_elementsMap;
    int m_rootElementId;
    QList<QWidget *> m_widgetStack;
};

#endif // WIDGETSTACK_H
