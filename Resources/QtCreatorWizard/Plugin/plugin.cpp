#include "%{HdrFileName}"
@if '%{PluginType}' === 'QWidget'
#include "ui_form.h"
@endif

%{CN}::%{CN}() :
	QObject(nullptr),
	PluginBase(this)
@if '%{PluginType}' === 'QWidget'
	, ui(new Ui::Form)
@endif
@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QWidget with QML'
	, m_uiElementBase(new UIElementBase(this, {""}))
@endif
{
@if '%{PluginType}' === 'QWidget'
	ui->setupUi(m_uiElementBase);
@endif
	initPluginBase(
		{
			{INTERFACE(IPlugin), this}
@if '%{PluginType}' === 'QWidget' || '%{PluginType}' === 'QWidget with QML'
			, {INTERFACE(IUIElement), m_uiElementBase}
@endif
@if %{CreateNewInterface}
			, {INTERFACE(%{InterfaceName}), /*this or instance*/ nullptr}
@endif
		},
		{},
		{}
	);
@if '%{PluginType}' === 'QWidget with QML'
	m_uiElementBase->initUIElementBase(
		{}, 
		{}
	);
	m_uiElementBase->setSource(QUrl("qrc:/form.qml"));
@endif
}

%{CN}::~%{CN}()
{
}
