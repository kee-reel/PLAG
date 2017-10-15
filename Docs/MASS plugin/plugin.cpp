#include "%{HdrFileName}"


@if '%{PluginType}' === 'View'
%{CN}::%{CN}(QWidget *parent) :
    QWidget(parent)/*,
    ui(new Ui::Form)*/
@else
    %{CN}::%{CN}() 
@endif
{
@if '%{PluginType}' === 'Model' || '%{PluginType}' === 'View' || '%{PluginType}' === 'DataManager'
    // myReferencedPlugin = NULL;
@endif
@if '%{PluginType}' === 'Model'
    openedView = NULL;
    openedModel = NULL;
@endif
    /*
    ui->setupUi(this);
    */
}

%{CN}::~%{CN}()
{
}

void %{CN}::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void %{CN}::OnAllSetup()
{

}

QString %{CN}::GetLastError()
{

}

void %{CN}::AddReferencePlugin(PluginInfo *pluginInfo)
{
@if '%{PluginType}' === 'Model' || '%{PluginType}' === 'View' || '%{PluginType}' === 'DataManager'
    /* Select your reference plugin case and get it. For example:
        case PLUGINMODEL:{
            myReferencedPlugin = qobject_cast<ISomePlugin*>(pluginInfo->Instance);
            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not ISomePlugin.";
                return;
            }
            qDebug() << "ISomePlugin succesfully set.";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;
    */

    switch(pluginInfo->Meta->Type){
        case PLUGINVIEW:{
@if '%{PluginType}' === 'Model'
            relatedViewPlugins.append(pluginInfo);
            qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
            connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
@endif
        } break;

        case PLUGINMODEL:{
@if '%{PluginType}' === 'Model'
            relatedModelPlugins.append(pluginInfo);
            qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
@endif
        } break;

        case ROOTMODEL:{
        } break;

        case DATAMANAGER:{
        }break;
    }
}

void %{CN}::ReferencePluginClosed(PluginInfo *pluginInfo)
{
    
}

@if '%{PluginType}' === 'Model'
bool %{CN}::Open(IModelPlugin *parent)
{
    qDebug() << "%{CN} open.";
    if(relatedViewPlugins.count() == 0){
        qDebug() << "!%{CN} hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "%{CN} opens related view " << openedView->Meta->Name;
    if(!openedView->Plugin.view->Open(this)){
        qDebug() << "!Can't open first view!";
        openedView = NULL;
        return false;
    }
    return true;
}
@elsif '%{PluginType}' === 'View'
bool %{CN}::Open(IModelPlugin *model)
{
    qDebug() << "%{CN} open.";

    // If something not set.
    if(false){ 
        qDebug() << "!%{CN} not fully initialized!";
        return false;
    }

    emit OnOpen(this);
    return true;
}
@endif

@if '%{PluginType}' === 'Model'
void %{CN}::Close()
{
    qDebug() << "%{CN} close.";
    if(openedView != NULL && !openedView->Plugin.view->Close()){
        qDebug() << "View plugin" << openedView->Meta->Name 
                 << "not closed, but model closing anyway.";
    }
    if(openedModel != NULL)
        openedView->Plugin.view->Close();

    openedView = NULL;
    openedModel = NULL;
    emit OnClose(pluginInfo);
    emit OnClose();
}
@elsif '%{PluginType}' === 'View'
bool %{CN}::Close()
{
    qDebug() << "%{CN} close.";
    // If view cannot close.
    if(false){ 
        qDebug() << "!%{CN} cannot close right now!";
        return false;
    }
    emit OnClose(pluginInfo);
    emit OnClose();
    return true;
}
@endif

@if '%{PluginType}' === 'DataSource'
void %{CN}::Setup()
{
    // Connect to your data source here.

}
@endif