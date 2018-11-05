#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QWidget>
#include <QList>
#include <QLayout>

#include "../../PluginsInterfaces/iuimanager.h"

#include "../../PluginsCommon/plugin_base.h"

//! addtogroup UIManager_imp
//! {
class UIManager : public PluginBase, public IUIManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IUIManager
    )

public:
    UIManager();
    virtual ~UIManager() override;

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
    QWidget *m_parentWidget;
    int m_rootElementId;
    QMap<int, QWeakPointer<IUIElement>> m_elementsMap;
    QList<QWidget *> m_widgetStack;
};
//! }
#endif // UIMANAGER_H
