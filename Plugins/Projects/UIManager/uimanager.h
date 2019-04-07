#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QWidget>
#include <QList>
#include <QLayout>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/iuimanager.h"
#include "../../Interfaces/ipluginlinker.h"

#include "uielement.h"

//! \addtogroup UIManager_imp
//!  \{
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

    // PluginBase interface
protected:
    virtual void onAllReferencesSet() override;

    // IUIManager interface
public:
    virtual const QWeakPointer<IUIElement> getRootElement() override;
    virtual const QVector<QWeakPointer<IUIElement> > getChildElements() override;

private:
    bool addRootItem(QWeakPointer<IPluginLinker::ILinkerItem> rootItem);
    bool addChildItem(QWeakPointer<IPluginLinker::ILinkerItem> item);
    bool removeChildItem(int elementId);
    void setupElementsLinks();

    bool validateElement(QWeakPointer<IUIElement> element);
    bool validateElementId(int elementId);
    int createElementIdForItem(QWeakPointer<IPluginLinker::ILinkerItem> item);
    QWeakPointer<IUIElement> getElementById(int elementId);

private slots:
    void onElementOpened(int elementId);
    void onElementClosed(int elementId);
    void onElementConnectionChanged(int elementId);
    void onLinkageFinished();

private:
    IPluginLinker* m_pluginLinker;

    QWidget *m_parentWidget;
    int m_rootElementId;
    QMap<int, QSharedPointer<UIElement>> m_elementsMap;
    QList<QWidget *> m_widgetStack;
};
//!  \}
#endif // UIMANAGER_H
