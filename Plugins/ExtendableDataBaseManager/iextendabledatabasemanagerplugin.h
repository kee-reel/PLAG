#ifndef ITASKDBTOOLPLUGIN_H
#define ITASKDBTOOLPLUGIN_H

#include "../../Plugins/MainMenuModelPlugin/interfaces.h"

template <class T> class QVector;
template <class T> class QList;
template <class A, class B> class QMap;
class QVariant;
enum QVariant::Type;

class IExtendableDataBaseManagerPlugin : public IDataManagerPlugin
{
public:
    class TreeItemInfo{
    public:
        int id;
        QMap<QString, QVector<QVariant>> dataChunks;
    };

    virtual QList<TreeItemInfo> GetData(QString treeName) = 0;
    virtual QMap<QString, QVariant::Type> GetTreeHeader(QString treeName) = 0;

    virtual bool SetRelation(QString mainName, QString relationName, QMap<QString, QVariant::Type> fields) = 0;
    virtual bool DeleteRelation(QString mainName, QString relationName) = 0;

    virtual int AddItem(QString treeName, TreeItemInfo task) = 0;
    virtual bool EditItem(QString treeName, TreeItemInfo task) = 0;
    virtual bool DeleteItem(QString treeName, int id) = 0;
};
Q_DECLARE_INTERFACE(IExtendableDataBaseManagerPlugin, "IExtendableDataBaseManagerPlugin v0.1")

#endif // ITASKDBTOOLPLUGIN_H
