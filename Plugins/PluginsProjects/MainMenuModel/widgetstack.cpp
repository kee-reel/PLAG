#include "widgetstack.h"

WidgetStack::WidgetStack(QWidget *parent) :
    QObject(parent)
{
    Q_ASSERT_X(parent, "WidgetStack initialization", "parent widget is null");
    parent->installEventFilter(this);
    parent->layout()->setMargin(0);
}

void WidgetStack::pop()
{
    qDebug() << "Pop" << m_widgetStack.last()->objectName();

    if (count() != 1)
    {
        m_widgetStack.last()->close();
        m_widgetStack.removeLast();
        m_widgetStack.last()->show();

    }
    else
    {
        QApplication::exit();
    }
}

void WidgetStack::push(QWidget *widget)
{
    qDebug() << "Push" << widget->objectName();

    if (count() != 0)
    {
        auto last = m_widgetStack.last();
        last->setVisible(false);
    }

    m_widgetStack.append(widget);
    QWidget *parentWidget = qobject_cast<QWidget *>(parent());
    widget->setParent(parentWidget);
    parentWidget->layout()->addWidget(widget);
    widget->show();
}

int WidgetStack::count()
{
    return m_widgetStack.length();
}

QWidget *WidgetStack::getTop()
{
    return m_widgetStack.last();
}

bool WidgetStack::eventFilter(QObject *watched, QEvent *event)
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

bool WidgetStack::init(QWeakPointer<IUIManager::IUIElement> rootElement)
{
    Q_ASSERT_X(addChildItem(rootElement), "WidgetStack::init", "rootElement already set");

    m_rootElementId = rootElement.data()->getElementId();
    return true;
}

bool WidgetStack::fini()
{
    if(!m_elementsMap.count())
    {
        return true;
    }

    auto elementsMapCopy = m_elementsMap;
    for(const auto &element : elementsMapCopy)
    {
        if(!removeChildItem(element))
        {
            qCritical() << QString("Error occured during UIManager finalization with element with id '%d'")
                        .arg(element.data()->getElementId());
        }
    }

    m_elementsMap.clear();
    return true;
}

bool WidgetStack::addChildItem(QWeakPointer<IUIManager::IUIElement> element)
{
    if(!validateElement(element))
    {
        qCritical() << "WidgetStack::addChildItem: skip element adding: validation fail";
        return false;
    }

    const auto &object = element.data()->getElementSignalsLinkObject();
    if(!object)
    {
        qCritical() << "WidgetStack::addChildItem: skip element adding: no QObject available";
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

bool WidgetStack::removeChildItem(QWeakPointer<IUIManager::IUIElement> element)
{
    if(!validateElement(element))
    {
        qCritical() << "WidgetStack::removeChildItem: skip element remove;";
        return false;
    }

    auto elementId = element.data()->getElementId();

    const auto &widget = element.data()->getElementWidget();
    widget->removeEventFilter(this);

    const auto &object = element.data()->getElementSignalsLinkObject();
    disconnect(object, SIGNAL(onOpened(int)),
               this, SLOT(onElementOpened(int)));
    disconnect(object, SIGNAL(OnClosed(int)),
               this, SLOT(onElementClosed(int)));
    disconnect(object, SIGNAL(onConnectionsChanged(int)),
               this, SLOT(onElementConnectionChanged(int)));

    m_elementsMap.remove(elementId);

    return true;
}

const QWeakPointer<IUIManager::IUIElement> WidgetStack::getRootElement()
{
    return m_elementsMap[m_rootElementId];
}

const QVector<QWeakPointer<IUIManager::IUIElement> > WidgetStack::getChildElements()
{
    auto &&mapCopy = m_elementsMap;
    mapCopy.remove(m_rootElementId);
    auto &&elementsList = mapCopy.values();
    return elementsList.toVector();
}

bool WidgetStack::validateElement(QWeakPointer<IUIManager::IUIElement> element) const
{
    if(element.isNull())
    {
        qCritical() << "WidgetStack::validateElement: element is empty.";
        return false;
    }

    auto elementId = element.data()->getElementId();
    if(m_elementsMap.contains(elementId))
    {
        qWarning() << QString("WidgetStack::validateElement: element with id '%1' already exist.").arg(elementId);
        return false;
    }

    return true;
}

const QWeakPointer<IUIManager::IUIElement> &WidgetStack::getElementById(int elementId) const
{
    const auto &elementIter = m_elementsMap.find(elementId);
    Q_ASSERT_X(elementIter != m_elementsMap.end(), "onOpen signal from element", "unknown element");

    return elementIter.value();
}

void WidgetStack::onElementOpened(int elementId)
{
    const auto &openedElement = getElementById(elementId);
    auto widget = openedElement.data()->getElementWidget();

    if(widget)
    {
        push(widget);
        return;
    }

    const auto connectedElements = openedElement.data()->getConnectedElements();
    QWeakPointer<IUIElement> connectedElement;
    for(const auto &element : connectedElements)
    {
        if(element.data()->getElementWidget())
        {
            element.data()->open(openedElement);
            break;
        }
    }
}

void WidgetStack::onElementClosed(int elementId)
{
    //const auto &element = getElementById(elementId);

    // TODO: provide logic for closing lower layer elements;
    pop();
}

void WidgetStack::onElementConnectionChanged(int elementId)
{

}
