#include "%{HdrFileName}"

%{CN}::%{CN}() :
    PluginBase(nullptr)
{
}

%{CN}::~%{CN}()
{
}

bool %{CN}::addReferencePlugin(const IPlugin *referencePlugin)
{
    return PluginBase::addReferencePlugin(referencePlugin);
}
