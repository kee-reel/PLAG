#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QAbstractItemModel>
#include <QResizeEvent>

#include "../../Plugins/TaskListModel/itasktreemodel.h"
#include "addform.h"
#include "mytreeview.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

    void SetModel(QAbstractItemModel *model);

private:

    void resizeEvent(QResizeEvent *event);

    Ui::MainForm *ui;
    AddForm *addForm;
    QAbstractItemModel *model;
    QTreeView *myTreeView;
    const QModelIndex *currentModelIndex;

signals:
    void onClose();
private slots:
    void on_buttonExit_clicked();
    void on_buttonAdd_clicked();
    void on_treeView_doubleClicked(const QModelIndex &index);
    void on_buttonDelete_clicked();
    void on_treeView_pressed(const QModelIndex &index);
    void on_buttonEdit_clicked();
};

#endif // MAINFORM_H
