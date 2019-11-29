#include "gamebuildingbase.h"
#include "gameeventhandler.hh"
#include "ui/customgraphicsitem.h"
#include "ui/customgraphicsscene.h"

GameBuildingBase::GameBuildingBase(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                                   const std::shared_ptr<Course::PlayerBase> &owner,
                                   CustomGraphicsScene *scene,
                                   const int &tilespaces,
                                   const Course::ResourceMap &buildcost,
                                   const Course::ResourceMap &production) :
    GameObjectBase(scene),
    Course::BuildingBase (eventhandler, objectmanager,owner, tilespaces, buildcost, production)
{

}

void GameBuildingBase::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    graphicsItem_ = graphicsItem;
    scene_ = scene;

    graphicsItem_->setShapePref(NO_SHAPE);
    graphicsItem_->setPixmap(QPixmap(":/resources/buildings/base.PNG"));


    qreal newX = this->getCoordinate().x() * TILE_SIZE;
    qreal newY = this->getCoordinate().y() * TILE_SIZE;

    scene_->addItem(graphicsItem_);
    graphicsItem_->setZValue(6);
    graphicsItem_->setPos(newX, newY);


    scene_->update();

    // std::shared_ptr<Course::TileBase> currentTile = lockObjectManager()->getTile(getCoordinate());
    std::shared_ptr<GraphicsTileBase> currentTile =
            std::dynamic_pointer_cast<GraphicsTileBase>(lockObjectManager()->getTile(getCoordinate()));
    std::vector<CustomGraphicsItem*> adjTiles;
    scene_->getAdjacentTiles(adjTiles, currentTile);

    std::shared_ptr<GameEventHandler> handler =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());

    for (auto tileObj : adjTiles) {
        std::weak_ptr<GraphicsTileBase> tile =
                std::dynamic_pointer_cast<GraphicsTileBase>(tileObj->getParentObject().lock());
        handler->claimTile(tile.lock().get());
    }
}

void GameBuildingBase::getMenuItems(QMenu &menu)
{
    menu.addSeparator();
    // tile can only be claimed if it has no owner

    QAction *workerHireAction = menu.addAction("Build worker");
    connect(workerHireAction, &QAction::triggered, this, &GameBuildingBase::buildUnit);

    //QAction *claimAction = menu.addAction("Claim");
    // connect(infoAction, &QAction::triggered, this, &GraphicsTileBase::sendInfo);
    // connect(claimAction, &QAction::triggered, this, &GraphicsTileBase::sendPtr);
}

void GameBuildingBase::buildUnit()
{
    std::shared_ptr<GameEventHandler> handler =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    handler->addUnit<GraphicsUnitBase>(lockObjectManager()->getTile(getCoordinate())->ID);
}
