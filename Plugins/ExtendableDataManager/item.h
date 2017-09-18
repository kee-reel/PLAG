#ifndef ITEM_H
#define ITEM_H

#include <QVector>
#include <QVariant>
#include <QDebug>
#include <QPixmap>
#include <QMap>

#include "iextendabledatamanager.h"

//! \addtogroup ExtendableDataBaseManagerPlugin_imp
//! \{
class Item : public IExtendableDataManager::ManagerDataItem
{
public:
    Item();
    Item(Item *parent, Item *copy);
    Item(Item *parent, int id, QString activeChunk, QMap<QString, QVector<QVariant>> dataChunks);
    ~Item();

// Columns and rows
    inline int ColumnCount() {
        return activeChunk ? activeChunk->count() : 0;
    }
    inline int GetRow() {
        return parentItem ? parentItem->GetChildPosition(this) : 0;
    }

// Childs
    void DetachFromParent();
    void SetChilds(QList<Item *> childs);
    void AddChild(Item *child, int row = INT32_MAX);
    void RemoveChild(Item *child);
    void RemoveChildAt(int row);
    inline Item *GetChildAt(int row) {
        return childItems.count() > row ? childItems[row] : NULL;
    }
    inline int ChildCount() {
        return childItems.count();
    }
    inline int GetChildPosition(Item *item) {
        return childItems.indexOf(item);
    }
    inline bool HasParent(){
        return parentItem != 0;
    }
    inline bool ParentIsRoot(){
        return parentItem ? !parentItem->HasParent() : false;
    }
    inline Item *GetParent(){
        return parentItem;
    }

// Data
    void SetOneChunkActive(QString &activeChunk);
    void ToggleChunkActive(QString &activeChunk);
    void ToggleAllChunksActive(QString &activeChunk);

    QList<QString> GetChunksNames() const;
    QVariant GetChunkName(int column) const;

    QVector<QVariant> GetChunkData(QString chunkName = "");
    void SetChunkData(QString chunkName, QVector<QVariant> data);

    QVector<QVariant> GetActiveChunksData();
    void SetActiveChunksData(QVector<QVariant> data);

    QMap<QString, QVariant> GetChunksData();
    void SetChunksData(QMap<QString, QVariant> dataMap);

    QVariant GetChunkDataElement(int column);
    void SetChunkDataElement(int column, QVariant data);

    QVariant GetDecoration();
    void SetDecoration(QVariant pixmap);

    inline int GetId() {
        return id;
    }
    inline void SetId(int id) {
        this->id = id;
    }

private:
    void SetParent(Item *parent);

    Item *parentItem;
    QString activeChunkName;
    QVector<QVariant> *activeChunk;

    QVariant *decoration;
    QList<Item*> childItems;
};
//! \}
#endif // TREEITEM_H
