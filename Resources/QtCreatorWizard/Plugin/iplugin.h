%{Cpp:LicenseTemplate}\
#ifndef I%{GUARD}
#define I%{GUARD}

#include <QtCore>

//! \defgroup %{CN}
//! \ingroup MainMenuPlugin_rel_m
//! \defgroup %{CN}_int Interface
//! \ingroup %{CN}
//! \defgroup %{CN}_imp Implementation
//! \ingroup %{CN}

//! \addtogroup %{CN}_int
//! \{
class %{InterfaceName}
{
public:
	
};
//! \}
Q_DECLARE_INTERFACE(%{InterfaceName}, "%{InterfaceName}")
#endif // I%{GUARD}
