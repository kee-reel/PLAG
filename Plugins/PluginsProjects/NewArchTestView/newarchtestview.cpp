#include "newarchtestview.h"

#include "ui_form.h"

NewArchTestView::NewArchTestView() :
    PluginBase(nullptr)
{
    connect(ui->pushButton, &QPushButton::clicked, this, [ = ]()
    {
        this->close(this);
    });
}

NewArchTestView::~NewArchTestView()
{
}
