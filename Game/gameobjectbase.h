#ifndef GAMEOBJECTBASE_H
#define GAMEOBJECTBASE_H

#include <QObject>
#include <QMenu>
#include "ui/customgraphicsscene.h"

static const unsigned int TILE_SIZE = 128;  // defines tile size (px)

class GameObjectBase : public QObject

{
    Q_OBJECT
public:
    GameObjectBase() = delete;

    GameObjectBase(CustomGraphicsScene* scene);

    ~GameObjectBase();

    virtual void getMenuItems(QMenu &menu);

    virtual bool getIsMovable() const;

    virtual bool getIsSelectable() const;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene);

protected:
    bool isMovable_;
    bool isSelectable_;

    CustomGraphicsItem *graphicsItem_;
    CustomGraphicsScene *scene_;

};

#endif // GAMEOBJECTBASE_H
