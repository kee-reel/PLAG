#ifndef IDataBase_H
#define IDataBase_H

#include <QtCore>

class QSqlQuery;

//!  \defgroup DataBase DataBase
//!      \ingroup Plugins
//!  \defgroup DataBase_int Interface
//!      \ingroup DataBase
//!  \defgroup DataBase_imp Implementation
//!      \ingroup DataBase
//!  \defgroup DataBase_dep Dependent plugins
//!      \ingroup DataBase


//! \addtogroup DataBase_int
//!  \{
//! \brief This interface determine data source as data base.
//!
//! Provides methods for interaction with data base with usage of SQL queries.
class IDataBase
{
public:
    //! \brief Execute query whithin connected data base using given string.
    //! \param Query string.
    //! \return Query result.
    //!
    virtual QSqlQuery ExecuteQuery(QString &query) = 0;
    //! \brief Execute query whithin connected data base using given string and parameters.
    //! \param Query string.
    //! \param Placeholders contained in string.
    //! \param Values that will be inserted in given placeholders.
    //! \return Query result.
    //!
    virtual QSqlQuery ExecuteQuery(QString &query, QList<QString> *valuePlaceholders, QList<QVariant> *values) = 0;

    virtual void SetPassword(QString password) = 0;

protected:
    virtual ~IDataBase() {}
};
Q_DECLARE_INTERFACE(IDataBase, "IDataBase v0.1")
//! @}

#endif // IDataBase_H
