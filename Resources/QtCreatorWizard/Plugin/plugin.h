%{Cpp:LicenseTemplate}\
#ifndef %{GUARD}
#define %{GUARD}

#include <QtCore>

#include "../../Interfaces/Architecture/PluginBase/plugin_base.h"
@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QWidget with QML'
#include "../../Interfaces/Architecture/UIElementBase/uielementbase.h"
@endif
@if '%{PluginType}' === 'QWidget'
namespace Ui
{
class Form;
}
@endif

@if %{CreateNewInterface}
#include "%{IPath}"

@endif
//! \addtogroup %{CN}_imp
//! \{
class %{CN} : public QObject, public PluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "MASS.Module.%{CN}" FILE "PluginMeta.json")
	Q_INTERFACES(
		IPlugin
	)

public:
	%{CN}();
	virtual ~%{CN}() override;

private:
@if '%{PluginType}' === 'QWidget'
	QSharedPointer<Ui::Form> ui;
@endif
@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QWidget with QML'
	UIElementBase* m_uiElementBase;
@endif
};
//! \}
#endif // %{GUARD}
