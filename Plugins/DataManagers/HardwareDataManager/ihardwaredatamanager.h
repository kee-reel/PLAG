#ifndef IHARDWAREDATAMANAGER_H
#define IHARDWAREDATAMANAGER_H

#include "../../interfaces.h"

#include

//! defgroup HardwareDataManager
//!     ingroup MainMenuPlugin_rel_m
//! defgroup HardwareDataManager_int Interface
//!     ingroup HardwareDataManager
//! defgroup HardwareDataManager_imp Implementation
//!     ingroup HardwareDataManager

//! addtogroup HardwareDataManager_int
//! {
class IHardwareDataManager :
    public IDataManagerPlugin
{
public:
    class IProtocolHandler
    {
    public:
        //!
        //! \brief CheckPortProtocolSupport
        //! \param portHandler - instance of QObject which provide.
        //! slot WriteData(QByteArray &data) and signal ReadData(QByteArray &data).
        //! \return Is protocol supported by device on given port.
        //!
        virtual bool CheckPortProtocolSupport(QObject* portHandler) = 0;

        //!
        //! \brief SetPort
        //! \param portHandler - instance of QObject which provide
        //! slot WriteData(QByteArray &data) and signal ReadData(QByteArray &data).
        //! \return Is port set.
        //! \details Set given port for this protocol handler - now all messages
        //! to port will be managed by it.
        //!
        virtual bool SetPort(QObject* portHandler) = 0;
    };

    void RegisterProtocolHandler(IProtocolHandler *instance) = 0;
};
//! }
Q_DECLARE_INTERFACE(IHardwareDataManager, "IHardwareDataManager")
#endif // IHARDWAREDATAMANAGER_H
