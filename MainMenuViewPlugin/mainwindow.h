#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QWidget>
#include <QString>

#include "draggablebutton.h"
#include "../TimeKeeper/interfaces.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void AddNewModuleView(MetaInfo *meta);

private:
    QList<DraggableButton*> modulesButtons;

private slots:


};

#endif // MAINWINDOW_H
