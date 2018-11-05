#if defined(PLUGIN_BASE_QWIDGET)
#include "plugin_base.h"
#include "ui_form.h"

PluginBase::PluginBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    constructorInit();
    ui->setupUi(this);
}
#endif
