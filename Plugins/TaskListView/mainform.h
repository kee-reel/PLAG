#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QAbstractItemModel>
#include "../../Plugins/TaskListModel/itasktreemodel.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

    void SetModel(QAbstractItemModel *taskTree);

    Ui::MainForm *ui;

signals:
    void onClose();
private slots:
    void on_buttonExit_clicked();
    void on_buttonAdd_clicked();
};

#endif // MAINFORM_H
