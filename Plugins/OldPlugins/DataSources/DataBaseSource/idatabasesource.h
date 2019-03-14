#ifndef IDATABASESOURCE_H
#define IDATABASESOURCE_H

#include "../../interfaces.h"

//! \brief This interface determine data source as data base.
//!
//! Provides methods for interaction with data base with usage of SQL queries.
class IDataBaseSourcePlugin : public IDataSourcePlugin
{
public:
    virtual ~IDataBaseSourcePlugin() {}
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
};
Q_DECLARE_INTERFACE(IDataBaseSourcePlugin, "IDataBaseSourcePlugin v0.1")

#endif // IDATABASESOURCE_H
