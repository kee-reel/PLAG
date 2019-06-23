%{Cpp:LicenseTemplate}\
#ifndef %{GUARD}
#define %{GUARD}

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../Common/plugin_base.h"

@if %{CreateNewInterface}
#include "../../Interfaces/%{IFileName}"

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
    Q_PLUGIN_METADATA(IID "MASS.Module.%{CN}" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
@if %{CreateNewInterface}
        %{InterfaceName}
@endif
    )

public:
    %{CN}();
    virtual ~%{CN}() override;
};
//! \}
#endif // %{GUARD}
