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
    inline QVariant GetId()             { return itemData[0]; }
    inline QVariant GetName()           { return itemData[1]; }
    inline void SetId(int id)           { itemData[0] = id; }
    inline void SetName(QString name)   { itemData[1] = name; }

    inline int GetRow() { return parentItem->GetChildPosition(this); }

    TreeItem *parentItem;
private:
    QList<QVariant> itemData;
    QList<TreeItem*> childItems;
};

#endif // TREEITEM_H
