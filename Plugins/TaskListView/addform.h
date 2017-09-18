#ifndef ADDFORM_H
#define ADDFORM_H

#include <QDebug>
#include <QWidget>
#include <QDataWidgetMapper>
#include <QAbstractItemModel>
#include <QKeyEvent>
#include <QMap>

namespace Ui {
class AddForm;
}
//! \addtogroup TaskListView_imp
//! \{
class AddForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddForm(QWidget *parent = 0);
    ~AddForm();

    void SetModel(QAbstractItemModel *model);
    void ShowModelData(const QModelIndex &index, bool isNew = false);

signals:
    void OnClose();

private:
    Ui::AddForm *ui;
    QDataWidgetMapper *mapper;

private slots:
    void on_buttonOk_clicked();
    void on_buttonClose_clicked();

    // QObject interface
public:
    bool event(QEvent *event) override;
};
//! \}
#endif // ADDFORM_H
