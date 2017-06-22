#ifndef ITEM_H
#define ITEM_H

#include <QVector>
#include <QVariant>
#include <QDebug>
#include <QPixmap>

//! \addtogroup ExtendableDataBaseManagerPlugin_imp
//! \{
class Item
{
public:
    Item *parentItem;

    Item();
    Item(Item *parent, Item *copy);
    Item(Item *parent, int id, QString activeChunk, QMap<QString, QVector<QVariant>> dataChunks);
    ~Item();

// Columns
    inline int ColumnCount() { return activeChunk ? activeChunk->count() : 0; }
    inline int GetRow() { return parentItem ? parentItem->GetChildPosition(this) : 0; }

// Childs
    void SetChilds(QList<Item *> childs);
    void AddChild(int row, Item *child);
    void RemoveChild(Item *child);
    void RemoveChildAt(int row);
    inline Item *GetChildAt(int row) { return childItems.count() > row ? childItems[row] : NULL; }
    inline int ChildCount() { return childItems.count(); }
    inline int GetChildPosition(Item *item) { return childItems.indexOf(item); }

// Data
    void SetActiveChunkName(QString &activeChunk);
    QList<QString> GetChunksNames();
    QVector<QVariant> GetChunkData(QString chunkName = "");
    QVariant GetChunkDataElement(int column);
    void SetChunkData(QString chunkName, QVector<QVariant> data);
    void SetChunkDataElement(int column, QVariant data);
    void SetDecoration(QVariant pixmap);
    QVariant GetDecoration();
    inline int GetId()              { return itemData.id; }
    inline void SetId(int id)       { itemData.id = id; }

private:
    class ItemData{
    public:
        int id;
        QMap<QString, QVector<QVariant>> dataChunks;
    };

    ItemData itemData;
    QVariant *decoration;
    QString activeChunkName;
    QVector<QVariant> *activeChunk;
    QList<Item*> childItems;
};
//! \}
#endif // TREEITEM_H
