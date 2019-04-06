#include "uielement.h"

UIElement::UIElement(QWeakPointer<IPluginLinker::ILinkerItem> linkerItem, QObject *parent) :
    QObject(parent),
    m_linkerItem(linkerItem)
{
    elementId = linkerItem.data()->getPluginUID();

    auto object = linkerItem.data()->getObject();
    connect(object, SIGNAL(onOpened(int)), this, SIGNAL(onOpened(int)));
    connect(object, SIGNAL(onClosed(int)), this, SIGNAL(onClosed(int)));
    connect(object, SIGNAL(onConnectionsChanged(int)), this, SIGNAL(onConnectionsChanged(int)));
}

UIElement::~UIElement()
{

}

bool UIElement::isOpened() const
{
    return m_linkerItem.data()->isOpened();
}

MetaInfo UIElement::getMeta() const
{
    return m_linkerItem.data()->getMeta();
}

int UIElement::getElementId() const
{
    return elementId;
}

QWidget *UIElement::getElementWidget() const
{
    return m_linkerItem.data()->getWidget();
}

const QObject *UIElement::getElementSignalsLinkObject() const
{
    return this;
}

QMap<int, QWeakPointer<IUIManager::IUIElement> > UIElement::getConnectedElements()
{
    QMap<int, QWeakPointer<IUIManager::IUIElement> > connectedElements;
    for(auto iter = m_connectedElements.begin(); iter != m_connectedElements.end(); ++iter)
    {
        connectedElements.insert(iter.key(), iter.value());
    }
    return connectedElements;
}

bool UIElement::open()
{
    return m_linkerItem.data()->open();
}

bool UIElement::close()
{
    return m_linkerItem.data()->close();
}

QVector<int> UIElement::getConnectedElementsIDs()
{
    auto references = m_linkerItem.data()->getReferences();
    auto referents = m_linkerItem.data()->getReferents();
    QVector<int> connectedElementsIDs;
    connectedElementsIDs.reserve(references.size() + referents.size());
    for(auto iter = references.begin(); iter != references.end(); ++iter)
    {
        connectedElementsIDs.append(iter.key());
    }
    for(auto iter = referents.begin(); iter != referents.end(); ++iter)
    {
        connectedElementsIDs.append(iter.key());
    }
    return connectedElementsIDs;
}

void UIElement::addConnectedElement(QWeakPointer<UIElement> element)
{
    m_connectedElements.insert(element.data()->getElementId(), element);
}

QWeakPointer<IPluginLinker::ILinkerItem> UIElement::getLinkerItem()
{
    return m_linkerItem;
}
