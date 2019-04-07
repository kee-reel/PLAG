#ifndef PARENTWINDOW_H
#define PARENTWINDOW_H

#include <QWidget>
#include <QScreen>
#include <QPainter>
#include <QResizeEvent>
#include <QVBoxLayout>

#include "pluginloader.h"

//! \brief Main application widget class.
class ParentWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ParentWindow(QWidget *parent = 0);
    virtual ~ParentWindow() override;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent* event) override;
    virtual void closeEvent(QCloseEvent *event) override;

public:
    bool Init();

private:
    void SetupWidget();

private:
    PluginLoader *pluginManager;
    QVBoxLayout *layout;
    const int MAX_TRIES_TO_CLOSE_APP = 2;
    int triesToCloseApp;
};
#endif // PARENTWINDOW_H
