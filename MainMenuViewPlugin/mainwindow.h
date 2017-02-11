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

    void AddNewButton(int id, QString task);

private:
    QList<DraggableButton*> modulesButtons;

signals:
    void OnButtonPressed(int);
};

#endif // MAINWINDOW_H
