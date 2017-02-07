#ifndef PARENTWINDOW_H
#define PARENTWINDOW_H

#include <QWidget>

#include "pluginmanager.h"

class ParentWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ParentWindow(QWidget *parent = 0);
private:
    PluginManager* pluginManager;
signals:

public slots:
};

#endif // PARENTWINDOW_H
