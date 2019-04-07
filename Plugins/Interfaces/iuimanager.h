#ifndef IUIMANAGER_H
#define IUIMANAGER_H

#include <QtCore>
#include "../Common/iplugin.h"

//!  \defgroup UIManager UIManager
//!      \ingroup Plugins
//!  \defgroup UIManager_int Interface
//!      \ingroup UIManager
//!  \defgroup UIManager_imp Implementation
//!      \ingroup UIManager
//!  \defgroup UIManager_dep Dependent plugins
//!      \ingroup UIManager

//!  \addtogroup UIManager_int
//!  \{
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

        virtual QMap<int, QWeakPointer<IUIElement> > getConnectedElements() = 0;

        virtual bool open() = 0;
        virtual bool close() = 0;

    signals:
        void onOpened(int selfId);
        void onClosed();
        void onConnectionsChanged();

    protected:
        virtual ~IUIElement() {}
    };

    virtual const QWeakPointer<IUIElement> getRootElement() = 0;
    virtual const QVector<QWeakPointer<IUIElement>> getChildElements() = 0;

protected:
    virtual ~IUIManager() {}
};
//!  \}
Q_DECLARE_INTERFACE(IUIManager, "IUIManager")
#endif // IUIMANAGER_H
