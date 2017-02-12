#ifndef PLUGINSTRUCTS_H
#define PLUGINSTRUCTS_H

#include <QString>

enum PluginTypes{
    TOOLMODEL,
    TOOLVIEW,
    DBMANAGER,
    DBTOOL,
    MAIN
};

struct MetaInfo{
    QString Name;
    PluginTypes Type;
    QString ParentPluginName;
};

#endif // PLUGINSTRUCTS_H
