#include "addform.h"
#include "ui_addform.h"

AddForm::AddForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddForm)
{
    ui->setupUi(this);
//    mapper = new QDataWidgetMapper(this);
    hide();
    connect(ui->buttonAccept, SIGNAL(clicked(bool)), SLOT(AcceptChanges()));
    connect(ui->buttonCancel, SIGNAL(clicked(bool)), SLOT(CancelChanges()));
    gridLayout = new QGridLayout(ui->scrollAreaWidgetContents);
}

AddForm::~AddForm()
{
    ClearEditors();
    delete gridLayout;
    delete ui;
}

void AddForm::SetModel(QAbstractItemModel *model)
{
    this->model = model;
//    mapper->setModel(model);
//    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

}

void AddForm::ShowModelData(const QModelIndex &index, bool isNew)
{
    show();
//    auto map = mapper->model()->itemData(index);
//    ui->label_2->setText();
    //ui->lineEdit_2->setFocus();
//    mapper->setRootIndex(index.parent());
//    mapper->setCurrentModelIndex(index);
//    if(isNew)
//        ui->lineEdit_2->setText("");
    currentModelIndex = index;
    auto rolesMap = model->itemData(currentModelIndex);
    currentItemMap = rolesMap[Qt::UserRole].toMap();
    auto iter = currentItemMap.begin();

    int rowCount = 0;
    while(iter != currentItemMap.end())
    {
        auto map = iter.value().toMap();
        auto mapIter = map.begin();
        while(mapIter != map.end())
        {
            labelsList.append(new QLabel(mapIter.key(), this));
            lineEdits.append(new QLineEdit(mapIter.value().toString(), this));
            gridLayout->addWidget(labelsList.last(), rowCount, 0);
            gridLayout->addWidget(lineEdits.last(), rowCount, 1);
            ++rowCount;
            ++mapIter;
        }
        ++iter;
    }
}

void AddForm::ClearEditors()
{
    for(int i = 0; i < labelsList.length(); ++i)
    {
        gridLayout->removeWidget(labelsList[i]);
        delete labelsList[i];
    }
    labelsList.clear();
    for(int i = 0; i < lineEdits.length(); ++i)
    {
        gridLayout->removeWidget(lineEdits[i]);
        delete lineEdits[i];
    }
    lineEdits.clear();
    currentItemMap.clear();
}

void AddForm::AcceptChanges()
{
    auto iter = currentItemMap.begin();
    int rowCount = 0;
    while(iter != currentItemMap.end())
    {
        auto map = iter.value().toMap();
        auto mapIter = map.begin();
        while(mapIter != map.end())
        {
            map[mapIter.key()] = QVariant(lineEdits[rowCount]->text());
            gridLayout->addWidget(lineEdits.last(), rowCount, 1);
            ++rowCount;
            ++mapIter;
        }
        currentItemMap[iter.key()] = QVariant(map);
        ++iter;
    }
    QMap<int, QVariant> rolesMap;
    rolesMap.insert(Qt::UserRole, currentItemMap);
    model->setItemData(currentModelIndex, rolesMap);
    ClearEditors();
    CancelChanges();
}

void AddForm::CancelChanges()
{
    hide();
    ClearEditors();
    emit OnClose();
}

bool AddForm::event(QEvent *event)
{
    switch (event->type()) {
        case QEvent::KeyRelease:{
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            switch (keyEvent->key()) {
            case Qt::Key_Enter:
                AcceptChanges();
                break;
            case Qt::Key_Escape:
                CancelChanges();
                break;
            default:
                return QWidget::event(event);
                break;
            }

        } break;
        default:
            return QWidget::event(event);
            break;
    }
}
