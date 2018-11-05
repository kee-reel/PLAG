#ifndef IUIMANAGER_H
#define IUIMANAGER_H

#include <QtCore>
#include "../PluginsCommon/iplugin.h"

//! defgroup UIManager
//!     ingroup MainMenuPlugin_rel_m
//! defgroup UIManager_int Interface
//!     ingroup UIManager
//! defgroup UIManager_imp Implementation
//!     ingroup UIManager

//! addtogroup UIManager_int
//! {
class IUIManager
{
public:
    class IUIElement
    {
    public:
        virtual bool isOpened() const = 0;
        virtual MetaInfo getMeta() const = 0;
        virtual int getElementId() const = 0;
        virtual QWidget *getElementWidget() const = 0;
        virtual const QObject *getElementSignalsLinkObject() const = 0;

        virtual QVector<QWeakPointer<IUIElement>> getConnectedElements() = 0;

        virtual bool open(QWeakPointer<IUIElement> openedByElement) = 0;
        virtual bool close(QWeakPointer<IUIElement> closedByElement) = 0;

    signals:
        void onOpened(int selfId);
        void onClosed(int selfId);
        void onConnectionsChanged(int selfId);

    protected:
        virtual ~IUIElement() {}
    };

    virtual bool init(QWeakPointer<IUIElement> rootElement) = 0;
    virtual bool fini() = 0;
    virtual bool addChildItem(QWeakPointer<IUIElement> element) = 0;
    virtual bool removeChildItem(QWeakPointer<IUIElement> element) = 0;

    virtual const QWeakPointer<IUIElement> getRootElement() = 0;
    virtual const QVector<QWeakPointer<IUIElement>> getChildElements() = 0;

protected:
    virtual ~IUIManager() {}
};
//! }
Q_DECLARE_INTERFACE(IUIManager, "IUIManager")
#endif // IUIMANAGER_H
