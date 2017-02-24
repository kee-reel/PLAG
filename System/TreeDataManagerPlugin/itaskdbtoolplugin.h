#ifndef ITASKDBTOOLPLUGIN_H
#define ITASKDBTOOLPLUGIN_H

#include "../../System/MASS/interfaces.h"

template <class T>
class QList;
template <class A, class B>
class QMap;
class QVariant;
enum QVariant::Type;
class ITreeDataManagerPlugin : public IDataManagerPlugin
{
public:
    class TreeItemInfo{
    public:
        int id;
        int parent;
        int position;
        QList<QVariant> data;
    };

    virtual QList<TreeItemInfo> GetTreeData(QString treeName) = 0;
    virtual QMap<QString, QVariant::Type> GetTreeHeader(QString treeName) = 0;

    virtual bool SetRelation(QString mainName, QString relationName, QMap<QString, QVariant::Type> fields) = 0;
    virtual bool DeleteRelation(QString mainName, QString relationName) = 0;

    virtual int AddItem(QString treeName, TreeItemInfo task) = 0;
    virtual bool EditItem(QString treeName, TreeItemInfo task) = 0;
    virtual bool DeleteItem(QString treeName, int id) = 0;
};
Q_DECLARE_INTERFACE(ITreeDataManagerPlugin, "ITreeDataManagerPlugin v0.1")

#endif // ITASKDBTOOLPLUGIN_H
