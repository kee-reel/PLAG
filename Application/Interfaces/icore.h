#pragma once


#include "iapplication.h"

class ICore
{
public:
	virtual void coreInit(quint32 corePluginUID, QObject* appObject, QWeakPointer<IApplication> app) = 0;

	virtual bool coreFini() = 0;
protected:
	virtual ~ICore() = default;
};
Q_DECLARE_INTERFACE(ICore, "ICore/1.0")
//! \}


