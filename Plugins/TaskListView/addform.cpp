#include "addform.h"
#include "ui_addform.h"

AddForm::AddForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddForm)
{
    ui->setupUi(this);
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
    auto editorsMap = model->headerData(0, Qt::Horizontal, Qt::UserRole).toMap();
    auto chunkIter = currentItemMap.begin();
    auto editorsChunkIter = editorsMap.begin();
    int rowCount = 0;
    while(chunkIter != currentItemMap.end())
    {
        auto valuesMap = chunkIter.value().toMap();
        auto valuesEditorsMap = editorsChunkIter.value().toMap();
        auto valueIter = valuesMap.begin();
        auto valueEditorsIter = valuesEditorsMap.begin();
        while(valueIter != valuesMap.end())
        {
            labelsList.append(new QLabel(valueIter.key(), this));
            gridLayout->addWidget(labelsList.last(), rowCount, 0);
            QWidget *editWidget;
            if(valueEditorsIter.value().isValid())
            {
                editWidget = (QWidget*)valueEditorsIter.value().value<void*>();
                editWidget->setObjectName("custom");
                editWidget->setProperty("value", valueIter.value());
            }
            else
            {
                editWidget = new QLineEdit(valueIter.value().toString(), this);
                editWidget->setObjectName("line");
            }
            editWidgets.append(editWidget);
            gridLayout->addWidget(editWidgets.last(), rowCount, 1);
            ++rowCount;
            ++valueIter;
            ++valueEditorsIter;
        }
        ++chunkIter;
        ++editorsChunkIter;
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
    for(int i = 0; i < editWidgets.length(); ++i)
    {
        gridLayout->removeWidget(editWidgets[i]);
        bool isDefaultEditor = editWidgets[i]->objectName() == "line";
        if(isDefaultEditor)
            delete editWidgets[i];
    }
    editWidgets.clear();
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
            bool isDefaultEditor = editWidgets[rowCount]->objectName() == "line";
            map[mapIter.key()] = editWidgets[rowCount]->property(isDefaultEditor ? "text" : "value");
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
