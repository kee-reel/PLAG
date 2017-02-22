#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>

class TreeItem
{
public:
    TreeItem();
    ~TreeItem();

    void SetChilds(QList<TreeItem *> childs);
    void AddChild(int row, TreeItem *child);
    inline TreeItem *GetChild(int row) { return childItems[row]; }
    inline int GetChildPosition(TreeItem *item) { return childItems.indexOf(item); }
    inline int ChildCount() { return childItems.count(); }

    inline static int columnCount()     { return 1; }
    inline QVariant GetId()             { return idData; }
    inline QVariant GetName()           { return nameData; }
    inline void SetId(int id)           { idData = id; }
    inline void SetName(QString name)   { nameData = name; }

    inline int GetRow() { return parentItem->GetChildPosition(this); }

    TreeItem *parentItem;
private:
    QVariant idData, nameData;
    QList<TreeItem*> childItems;
};

#endif // TREEITEM_H
