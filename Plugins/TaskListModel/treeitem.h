#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>

class TreeItem
{
public:
    TreeItem();
    TreeItem(TreeItem *parent, int id, QList<QVariant> data);
    ~TreeItem();


    void SetChilds(QList<TreeItem *> childs);
    void AddChild(int row, TreeItem *child);
    inline TreeItem *GetChild(int row) { return childItems[row]; }
    inline int GetChildPosition(TreeItem *item) { return childItems.indexOf(item); }
    inline int ChildCount() { return childItems.count(); }

    inline static int columnCount() { return dataColumnsCount; }

    inline int GetId()              { return id; }
    QVariant GetCoreData();
    QVariant GetData(int column);

    inline void SetId(int id)       { this->id = id; }
    void SetData(int column, QVariant data);
    void SetCoreData(QVariant data);

    inline int GetRow() { return parentItem->GetChildPosition(this); }

    TreeItem *parentItem;
private:
    int id;
    QList<QVariant> itemData;
    QList<TreeItem*> childItems;

    static const int coreDataIndex = 1;
    static const int dataColumnsCount = 1;

};

#endif // TREEITEM_H
