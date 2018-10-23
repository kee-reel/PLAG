#ifndef INEWARCHTESTPLUGIN_H
#define INEWARCHTESTPLUGIN_H

#include <QtCore>

//! defgroup NewArchTestPlugin
//!     ingroup MainMenuPlugin_rel_m
//! defgroup NewArchTestPlugin_int Interface
//!     ingroup NewArchTestPlugin
//! defgroup NewArchTestPlugin_imp Implementation
//!     ingroup NewArchTestPlugin

//! addtogroup NewArchTestPlugin_int
//! {
class INewArchTestPlugin
{
public:
    virtual ~INewArchTestPlugin() = 0;

    virtual int someMethod(int x) = 0;
};
//! }
Q_DECLARE_INTERFACE(INewArchTestPlugin, "INewArchTestPlugin")
#endif // INEWARCHTESTPLUGIN_H
