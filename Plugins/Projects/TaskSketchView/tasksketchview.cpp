#include "tasksketchview.h"
#include "ui_form.h"

TaskSketchView::TaskSketchView(QWidget* parent) :
    PluginBase(parent)
{
    paintWidgetTypeEditor = nullptr;
    myModel = nullptr;
    galleryForm = new GalleryForm(this);
    galleryForm->setVisible(false);
    imageFormat = "png";
    connect(ui->buttonSave, SIGNAL(clicked(bool)), SLOT(on_buttonSave_clicked()));
    connect(ui->buttonClear, SIGNAL(clicked(bool)), ui->widgetPaint, SLOT(Clean()));
    connect(ui->buttonOpenGallery, SIGNAL(clicked(bool)), SLOT(on_buttonOpenGallery_clicked()));
    connect(ui->buttonClose, SIGNAL(clicked(bool)), SLOT(on_buttonClose_clicked()));

    connect(galleryForm, SIGNAL(OnItemDelete(int)), SLOT(OnItemDelete(int)));
    connect(galleryForm, SIGNAL(OnItemConvert(int)), SLOT(OnItemConvertSlot(int)));

#ifdef Q_OS_ANDROID
    ui->buttonClear->setFocusPolicy(Qt::NoFocus);
    ui->buttonClear->setToolTip("");
    ui->buttonOpenGallery->setFocusPolicy(Qt::NoFocus);
    ui->buttonOpenGallery->setToolTip("");
    ui->buttonSave->setFocusPolicy(Qt::NoFocus);
    ui->buttonSave->setToolTip("");
    ui->buttonClose->setVisible(false);
#endif
}

TaskSketchView::~TaskSketchView()
{
    delete galleryForm;

    if(paintWidgetTypeEditor && paintWidgetTypeEditor->parent())
        delete paintWidgetTypeEditor;
}

void TaskSketchView::resizeEvent(QResizeEvent *event)
{
    galleryForm->setGeometry(rect());
}

void TaskSketchView::OnItemDelete(int index)
{
    sketchModel->removeRows(index, 1);
}

void TaskSketchView::OnItemConvertSlot(int index)
{
    myModel->ConvertSketchToTask(index);
}

void TaskSketchView::on_buttonClear_clicked()
{
    ui->widgetPaint->Clean();
}

void TaskSketchView::on_buttonSave_clicked()
{
    QByteArray array = ui->widgetPaint->value().toByteArray();

    sketchModel->insertRows(0, 1);
    QModelIndex root = sketchModel->index(0, 0);
    sketchModel->setData(root, QVariant(array));
    galleryForm->AddImage(0, array);
}

void TaskSketchView::on_buttonOpenGallery_clicked()
{
    galleryForm->show();
}

void TaskSketchView::on_buttonClose_clicked()
{
    emit onClose(this);
}

void TaskSketchView::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "ITaskSketchModel", Qt::CaseInsensitive))
        {
            myModel = castPluginToInterface<ITaskSketchModel>(plugin);
        }
    }
    PluginBase::onAllReferencesSet();
}

void TaskSketchView::onAllReferencesReady()
{
    paintWidgetTypeEditor = new PaintWidget();
    myModel->LinkEditorWidget(paintWidgetTypeEditor);

    taskModel = myModel->GetModel();
    sketchModel = myModel->GetInternalModel();
    galleryForm->SetModel(sketchModel);

    int n = sketchModel->rowCount();
    for(int i = 0; i < n; ++i)
    {
        QModelIndex index = sketchModel->index(i, 0);
        QByteArray ba = index.data().toByteArray();
        galleryForm->AddImage(i, ba);
    }

    PluginBase::onAllReferencesReady();
}
