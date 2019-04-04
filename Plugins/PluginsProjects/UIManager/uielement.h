#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "../../PluginsInterfaces/iuimanager.h"
#include "../../PluginsInterfaces/ipluginlinker.h"

class UIElement : public QObject, public IUIManager::IUIElement
{
    Q_OBJECT
public:
    UIElement(QWeakPointer<IPluginLinker::ILinkerItem> linkerItem, QObject* parent = nullptr);
    ~UIElement();

    // IUIElement interface
public:
    bool isOpened() const;
    MetaInfo getMeta() const;
    int getElementId() const;
    QWidget *getElementWidget() const;
    const QObject *getElementSignalsLinkObject() const;
    QMap<int, QWeakPointer<IUIElement> > getConnectedElements();
    bool open();
    bool close();

signals:
    void onOpened(int elementId);
    void onClosed(int elementId);
    void onConnectionsChanged(int elementId);

public:
    QVector<int> getConnectedElementsIDs();
    void addConnectedElement(QWeakPointer<UIElement> element);

private:
    QWeakPointer<IPluginLinker::ILinkerItem> getLinkerItem();

private:
    int elementId;
    QWeakPointer<IPluginLinker::ILinkerItem> m_linkerItem;
    QMap<int, QWeakPointer<UIElement> > m_connectedElements;
};

#endif // UIELEMENT_H
