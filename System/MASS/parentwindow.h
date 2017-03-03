#ifndef PARENTWINDOW_H
#define PARENTWINDOW_H

#include <QWidget>
#include <QScreen>
#include <QPainter>
#include <QResizeEvent>

#include "pluginloader.h"

class ParentWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ParentWindow(QWidget *parent = 0);
private:
    PluginLoader* pluginManager;

signals:

public slots:
};

#endif // PARENTWINDOW_H
