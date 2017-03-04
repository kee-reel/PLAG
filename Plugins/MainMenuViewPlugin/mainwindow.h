#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QWidget>
#include <QString>
#include <QPainter>

#include "draggablebutton.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void AddNewButton(int id, QString task);
    void WipeAllButtons();
private:
    QList<DraggableButton*> modulesButtons;
    void paintEvent(QPaintEvent *event);

signals:
    void OnButtonPressed(int);
};

#endif // MAINWINDOW_H
