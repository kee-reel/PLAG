#ifndef GRIDMAINMENUVIEW_H
#define GRIDMAINMENUVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QScroller>

#include "../../Interfaces/iuimanager.h"
#include "../../Common/plugin_base.h"

#include "uniquepushbutton.h"
#include "aspectawaregridlayout.h"

//! \addtogroup UIManager_dep
//!  \{
class GridMainMenuView : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
    )

public:
    explicit GridMainMenuView();
    virtual ~GridMainMenuView() override;

private:
    //    QQuickView *quickView;
    //    QWidget *container;

    IUIManager *m_uiManager;

    QLayout *layout;
    QMap<int, QWeakPointer<IUIManager::IUIElement>> m_uiElements;
    int m_uniqueIdCounter;
    QVector<UniquePushButton *> m_uniqueButtons;
    UniquePushButton *m_exitItem;

private slots:
    void UniqueButtonPressed(UniquePushButton *button);
    QString FormatMenuItemName(QString name);

private:
    int getUniqueId();

signals:
    void OnOpen(QWidget *);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;

    // PluginBase interface
protected:
    virtual void onAllReferencesSet() override;

    // IPlugin interface
public:
    virtual bool open() override;

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};
//!  \}
#endif // GRIDMAINMENUVIEW_H
