#include "uimanager.h"

UIManager::UIManager() :
    PluginBase()
{
}

UIManager::~UIManager()
{
    if(!m_elementsMap.count())
    {
        return;
    }

    auto elementsMapCopy = m_elementsMap;
    for(const auto &element : elementsMapCopy)
    {
        if(!removeChildItem(element.get()->getElementId()))
        {
            qCritical() << QString("Error occured during UIManager finalization with element with id '%d'")
                        .arg(element.data()->getElementId());
        }
    }

    m_elementsMap.clear();
}

void UIManager::pop()
{
    qDebug() << "Pop" << m_widgetStack.last()->objectName();

    if (count() != 1)
    {
        auto last = m_widgetStack.last();
        last->setParent(nullptr);
        last->close();
        m_widgetStack.removeLast();
        m_widgetStack.last()->show();

    }
    else
    {
        QApplication::exit();
    }
}

void UIManager::push(QWidget *widget)
{
    qDebug() << "Push" << widget->objectName();

    if (count() != 0)
    {
        auto last = m_widgetStack.last();
        last->setVisible(false);
    }

    m_widgetStack.append(widget);
    widget->setParent(m_parentWidget);
    m_parentWidget->layout()->addWidget(widget);
    widget->show();
}

int UIManager::count()
{
    return m_widgetStack.length();
}

QWidget *UIManager::getTop()
{
    return m_widgetStack.last();
}

bool UIManager::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Back)
        {
            pop();
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}

bool UIManager::addRootItem(QWeakPointer<IPluginLinker::ILinkerItem> rootItem)
{
    m_parentWidget = rootItem.data()->getWidget();
    Q_ASSERT_X(m_parentWidget, "UIManager initialization", "parent widget is null");
    Q_ASSERT_X(addChildItem(rootItem), "UIManager::init", "rootElement already set");

    m_parentWidget->installEventFilter(this);
    m_parentWidget->layout()->setMargin(0);
    m_rootElementId = rootItem.data()->getPluginUID();
    return true;
}

bool UIManager::addChildItem(QWeakPointer<IPluginLinker::ILinkerItem> item)
{
    auto element = QSharedPointer<UIElement>(new UIElement(item));
    if(!validateElement(element))
    {
        qCritical() << "UIManager::addChildItem: skip element adding: validation fail";
        return false;
    }

    const auto &object = element.data()->getElementSignalsLinkObject();
    if(!object)
    {
        qCritical() << "UIManager::addChildItem: skip element adding: no QObject available";
        return false;
    }
    // TODO: add connect success checking; if failure skip adding.
    connect(object, SIGNAL(onOpened(int)), this, SLOT(onElementOpened(int)));
    connect(object, SIGNAL(onClosed(int)), this, SLOT(onElementClosed(int)));
    connect(object, SIGNAL(onConnectionsChanged(int)), this, SLOT(onElementConnectionChanged(int)));

    const auto &widget = element.data()->getElementWidget();
    if(widget)
    {
        widget->installEventFilter(this);
    }

    auto elementId = element.data()->getElementId();
    m_elementsMap.insert(elementId, element);

    return true;
}

bool UIManager::removeChildItem(int elementId)
{
    if(!validateElementId(elementId))
    {
        qCritical() << "UIManager::removeChildItem: skip element remove;";
        return false;
    }

    auto element = getElementById(elementId);

    const auto &widget = element.data()->getElementWidget();
    widget->removeEventFilter(this);
    widget->setParent(nullptr);

    const auto &object = element.data()->getElementSignalsLinkObject();
    disconnect(object, SIGNAL(onOpened(int)), this, SLOT(onElementOpened(int)));
    disconnect(object, SIGNAL(OnClosed(int)), this, SLOT(onElementClosed(int)));
    disconnect(object, SIGNAL(onConnectionsChanged(int)), this, SLOT(onElementConnectionChanged(int)));

    m_elementsMap.remove(elementId);

    return true;
}

void UIManager::setupElementsLinks()
{
    for(auto element : m_elementsMap)
    {
        auto connectionIds = element.data()->getConnectedElementsIDs();
        for(auto connectionId : connectionIds)
        {
            element->addConnectedElement(m_elementsMap[connectionId]);
        }
    }
}

const QWeakPointer<IUIManager::IUIElement> UIManager::getRootElement()
{
    auto &&element = m_elementsMap[m_rootElementId];
    return element;
}

const QVector<QWeakPointer<IUIManager::IUIElement> > UIManager::getChildElements()
{
    auto mapCopy = m_elementsMap;
    mapCopy.remove(m_rootElementId);
    QVector<QWeakPointer<IUIManager::IUIElement> > childVector;
    childVector.reserve(mapCopy.count());
    for(auto element : m_elementsMap)
    {
        childVector.append(element);
    }
    return childVector;
}

bool UIManager::validateElement(QWeakPointer<IUIManager::IUIElement> element)
{
    if(element.isNull())
    {
        qCritical() << "UIManager::validateElement: element is empty.";
        return false;
    }

    return validateElementId(element.data()->getElementId());
}

bool UIManager::validateElementId(int elementId)
{
    if(m_elementsMap.contains(elementId))
    {
        qWarning() << QString("UIManager::validateElement: element with id '%1' already exist.").arg(elementId);
        return false;
    }

    return true;
}

int UIManager::createElementIdForItem(QWeakPointer<IPluginLinker::ILinkerItem> item)
{
    return item.data()->getPluginUID();
}

QWeakPointer<IUIManager::IUIElement> UIManager::getElementById(int elementId)
{
    const auto &elementIter = m_elementsMap.find(elementId);
    Q_ASSERT_X(elementIter != m_elementsMap.end(), "onOpen signal from element", "unknown element");

    return elementIter.value();
}

void UIManager::onElementOpened(int elementId)
{
    const auto &openedElement = getElementById(elementId);
    auto widget = openedElement.data()->getElementWidget();
    qDebug() << "Opened" << openedElement.data()->getMeta().Name;

    if(widget && widget != m_parentWidget)
    {
        push(widget);
        return;
    }

    const auto connectedElements = openedElement.data()->getConnectedElements();
    bool isOpened = false;
    for(const auto &element : connectedElements)
    {
        auto &&elementPtr = element.data();
        if(!elementPtr->isOpened() && elementPtr->getElementWidget())
        {
            elementPtr->open();
            isOpened = true;
            break;
        }
    }

    if(!isOpened)
    {
        for(const auto &element : connectedElements)
        {
            auto &&elementPtr = element.data();
            if(!elementPtr->isOpened())
            {
                elementPtr->open();
                isOpened = true;
                break;
            }
        }
    }

    if(!isOpened)
    {
        auto &&meta = openedElement.data()->getMeta();
        qCritical() << QString("No connected to elements found to open [%1 : %2]")
                    .arg(meta.Name).arg(meta.InterfaceName);
    }
}

void UIManager::onElementClosed(int elementId)
{
    //const auto &element = getElementById(elementId);

    // TODO: provide logic for closing lower layer elements;
    pop();
}

void UIManager::onElementConnectionChanged(int elementId)
{

}

void UIManager::onLinkageFinished()
{
    auto plugins = m_pluginLinker->getPluginsMap();

    auto coreItemUID = m_pluginLinker->getCorePluginUID();
    auto rootItem = plugins[coreItemUID];
    addRootItem(rootItem);
    plugins.remove(coreItemUID);

    for(auto iter = plugins.begin(); iter != plugins.end(); ++iter)
    {
        addChildItem(iter.value());
    }

    setupElementsLinks();
}

void UIManager::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IPluginLinker", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            m_pluginLinker = qobject_cast<IPluginLinker*>(instance);
            connect(instance, SIGNAL(onLinkageFinished()), this, SLOT(onLinkageFinished()));
        }
    }
    PluginBase::onAllReferencesSet();
}
