#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QAbstractItemModel>
#include <QResizeEvent>

#include "../../Models/TaskListModel/itasktreemodel.h"
#include "addform.h"
#include "mytreeview.h"

namespace Ui {
class MainForm;
}
//! \addtogroup TaskListView_imp
//! \{
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
    bool expandFlag;
    const QModelIndex *currentModelIndex;

signals:
    void onClose();

private slots:
    void OnAddFormClosed();

    void on_buttonExit_clicked();
    void on_buttonAdd_clicked();
    void on_buttonDelete_clicked();
    void onTreeViewPressed(const QModelIndex &index);
    void on_buttonEdit_clicked();
    void onTreeViewClicked(const QModelIndex &index);
};
//! \}
#endif // MAINFORM_H
