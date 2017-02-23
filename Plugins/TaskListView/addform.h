#ifndef ADDFORM_H
#define ADDFORM_H

#include <QWidget>
#include <QDataWidgetMapper>
#include <QAbstractItemModel>

namespace Ui {
class AddForm;
}

class AddForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddForm(QWidget *parent = 0);
    ~AddForm();

    void SetModel(QAbstractItemModel *model);
    void ShowModelData(const QModelIndex &index);

    QDataWidgetMapper *mapper;
private:
    Ui::AddForm *ui;

private slots:
    void on_buttonOk_clicked();
    void on_buttonClose_clicked();
};

#endif // ADDFORM_H
