%{Cpp:LicenseTemplate}\
#ifndef %{GUARD}
#define %{GUARD}

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../PluginsCommon/plugin_base.h"

@if %{CreateNewInterface}
#include "../../PluginsInterfaces/%{IFileName}"

@endif
//! \addtogroup %{CN}_imp
//! \{
class %{CN} : 
@if %{CreateNewInterface}
    public PluginBase,
    public %{InterfaceName}
@else
    public PluginBase
@endif
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
@if %{CreateNewInterface}
        %{InterfaceName}
@endif
    )

public:
    %{CN}();
    virtual ~%{CN}() override;

    // PluginBase interface
public:
    virtual bool addReferencePlugin(const IPlugin *referencePlugin) override;
};
//! \}
#endif // %{GUARD}
