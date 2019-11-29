#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <memory>
#include "tiles/graphicstilebase.h"
#include "ui/customgraphicsitem.h"

class CustomGraphicsItem;

class GameEventHandler;

class ObjectManager;

class GameObjectBase;

class CustomGraphicsScene : public QGraphicsScene
{
public:
    CustomGraphicsScene(QObject *parent = nullptr);

    virtual ~CustomGraphicsScene() = default;

    void setupMap(const std::vector<std::shared_ptr<Course::TileBase>>& tiles);

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent) override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    void getAdjacentTiles(std::vector<CustomGraphicsItem* > &tileVec,
                          std::shared_ptr<GraphicsTileBase> tile,
                          const unsigned int range = 999,
                          GraphicsUnitBase* unit = nullptr);

    void toggleTileHighlight(std::vector<CustomGraphicsItem *> &tileVec, bool value = false);

public slots:
    void enterMovementMode();

protected:
    bool movementModeFlag_ = false;
    CustomGraphicsItem *lastClickedItem_ = nullptr;
    std::vector<CustomGraphicsItem*> tileVec_ = {};

    std::shared_ptr<GameEventHandler> eventHandler_;
    std::shared_ptr<ObjectManager> objectManager_;
};

#endif // CUSTOMGRAPHICSSCENE_H
