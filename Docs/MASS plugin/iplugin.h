%{Cpp:LicenseTemplate}\
#ifndef I%{GUARD}
#define I%{GUARD}

#include "../../interfaces.h"

//! \defgroup %{CN}
//!     \ingroup MainMenuPlugin_rel_m
//! \defgroup %{CN}_int Interface
//!     \ingroup %{CN}
//! \defgroup %{CN}_imp Implementation
//!     \ingroup %{CN}

//! \addtogroup %{CN}_int
//! \{
class %{InterfaceName} : 
@if '%{PluginType}' === 'RootModel' || '%{PluginType}' === 'Model'
	public IModelPlugin
@elsif '%{PluginType}' === 'View'
	public IViewPlugin
@elsif '%{PluginType}' === 'DataManager'
	public IDataManagerPlugin
@elsif '%{PluginType}' === 'DataSource'
	public IDataSourcePlugin
@endif
{
public:
    // Write your interface methods here
};
//! \}
Q_DECLARE_INTERFACE(%{InterfaceName}, "%{InterfaceName}")
#endif // I%{GUARD}
