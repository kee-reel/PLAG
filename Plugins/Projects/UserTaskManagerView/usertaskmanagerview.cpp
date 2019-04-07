#include "usertaskmanagerview.h"
#include "ui_form.h"

UserTaskManagerView::UserTaskManagerView(QWidget* parent) :
    PluginBase(parent)
{
    myModel = nullptr;
    taskTree = nullptr;
    proxyModel = nullptr;

    myTreeView = new QTreeView(this);// MyTreeView(this);
    ui->verticalLayout->setDirection(QBoxLayout::BottomToTop);
    ui->verticalLayout->addWidget(myTreeView);

    connect(ui->buttonAdd, &QPushButton::clicked, this, &UserTaskManagerView::on_buttonAdd_clicked);
    connect(ui->buttonEdit, &QPushButton::clicked, this, &UserTaskManagerView::on_buttonEdit_clicked);
    connect(ui->buttonDelete, &QPushButton::clicked, this, &UserTaskManagerView::on_buttonDelete_clicked);
    connect(ui->buttonExit, &QPushButton::clicked, this, &UserTaskManagerView::on_buttonExit_clicked);

    connect(myTreeView, SIGNAL(clicked(QModelIndex)), SLOT(onTreeViewClicked(QModelIndex)));
    connect(myTreeView, SIGNAL(doubleClicked(QModelIndex)), SLOT(onTreeViewDoubleClicked(QModelIndex)));
    connect(myTreeView, SIGNAL(pressed(QModelIndex)), SLOT(onTreeViewPressed(QModelIndex)));
    myTreeView->setExpandsOnDoubleClick(false);

#ifdef Q_OS_ANDROID
    ui->buttonAdd->setFocusPolicy(Qt::NoFocus);
    ui->buttonAdd->setToolTip("");
    ui->buttonDelete->setFocusPolicy(Qt::NoFocus);
    ui->buttonDelete->setToolTip("");
    ui->buttonEdit->setFocusPolicy(Qt::NoFocus);
    ui->buttonEdit->setToolTip("");
    ui->buttonExit->setVisible(false);
#endif

    addForm = new AddForm(this);
    connect(addForm, SIGNAL(OnClose()), this, SLOT(OnAddFormClosed()));
}

UserTaskManagerView::~UserTaskManagerView()
{

}

void UserTaskManagerView::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IUserTaskManager", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            myModel = qobject_cast<IUserTaskManager*>(instance);
            //connect(pluginInfo->Instance, SIGNAL(OpenTaskEdit(int)), SLOT(OpenTaskEditor(int)));
        }
    }
    PluginBase::onAllReferencesSet();
}

void UserTaskManagerView::onAllReferencesReady()
{
    taskTree = myModel->GetTreeModel();
    model = new DesignProxyModel(taskTree);
    currentModelIndex = nullptr;
    myTreeView->setModel(model);
    addForm->SetModel(model);

    PluginBase::onAllReferencesReady();
}

void UserTaskManagerView::OpenTaskEditor(int id)
{
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!" << id;
}

void UserTaskManagerView::resizeEvent(QResizeEvent *event)
{
    qDebug() << "Resize";
    addForm->resize(event->size());
}

void UserTaskManagerView::OnAddFormClosed()
{
    show();
    ui->buttonAdd->setFocusPolicy(Qt::StrongFocus);
    ui->buttonDelete->setFocusPolicy(Qt::StrongFocus);
    ui->buttonEdit->setFocusPolicy(Qt::StrongFocus);
    ui->buttonExit->setFocusPolicy(Qt::StrongFocus);
    myTreeView->setFocusPolicy(Qt::StrongFocus);
    myTreeView->setFocus();
}

void UserTaskManagerView::on_buttonExit_clicked()
{
    emit onClose(this);
}

void UserTaskManagerView::on_buttonAdd_clicked()
{
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    QModelIndex newIndex;
    if(list.count())
    {
        model->insertRows(model->rowCount(list.first()), 1, list.first());
        myTreeView->expand(list.first());
        newIndex = model->index(model->rowCount(list.first())-1, 0, list.first());
    }
    else
    {
        model->insertRows(-1, 1);
        newIndex = model->index(model->rowCount()-1, 0);
    }
    addForm->ShowModelData(newIndex, true);
}

void UserTaskManagerView::on_buttonDelete_clicked()
{
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    for(int i = list.count()-1; i >= 0; --i) {
        model->removeRows(list[i].row(), 1, list[i].parent());
    }
}

void UserTaskManagerView::on_buttonEdit_clicked()
{
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    if(list.count())
        addForm->ShowModelData(list.first());
}

void UserTaskManagerView::onTreeViewPressed(const QModelIndex &index)
{
    currentModelIndex = &index;
}

void UserTaskManagerView::onTreeViewClicked(const QModelIndex &index)
{
    if(expandFlag)
        expandFlag = false;
    else
    {
        myTreeView->setExpanded(index, !myTreeView->isExpanded(index));
        expandFlag = true;
    }
}
