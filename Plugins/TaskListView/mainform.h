#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QPainter>
#include "../../Plugins/TaskListModel/itasklistmodel.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private:
    Ui::MainForm *ui;
    ITaskListModel::TaskInfo *rootTask;

//    void paintEvent(QPaintEvent *event);
//    void mousePressEvent(QMouseEvent *event);

signals:
    void onClose();
private slots:
    void on_pushButton_clicked();
};

#endif // MAINFORM_H
