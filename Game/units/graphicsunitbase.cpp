#include "graphicsunitbase.h"
#include "tiles/graphicstilebase.h"
#include "ui/customgraphicsscene.h"
#include "gameeventhandler.hh"


GraphicsUnitBase::GraphicsUnitBase(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                                   const std::shared_ptr<Course::PlayerBase> &owner,
                                   CustomGraphicsScene* scene,
                                   const int &tilespaces,
                                   const Course::ResourceMap &cost,
                                   const Course::ResourceMapDouble &efficiency) :
    Course::WorkerBase (eventhandler, objectmanager, owner, tilespaces, cost, efficiency),
    GameObjectBase (scene)
{

}

bool GraphicsUnitBase::isMovable() const
{
    return true;
}

void GraphicsUnitBase::getMenuItems(QMenu &menu)
{
    QAction* infoAction = menu.addAction("Info");

    QAction* moveAction = menu.addAction("Move");

    if (movePoints_ == 0) {
        moveAction->setDisabled(true);
    }

    connect(moveAction, &QAction::triggered, this, &GraphicsUnitBase::initMove);
}

void GraphicsUnitBase::doSpecialAction()
{

}

unsigned int GraphicsUnitBase::getMovePoints()
{
    return movePoints_;
}

bool GraphicsUnitBase::moveToTile(std::shared_ptr<GraphicsTileBase> tileToMoveTo, bool ignoreMovePoints)
{
    if (canMoveToTile(tileToMoveTo.get())) {
        if (!ignoreMovePoints) {
            movePoints_ -= tileToMoveTo->getMovementCost();
        }
        setCoordinate(tileToMoveTo->getCoordinate());

        QPointF itemLoc = tileToMoveTo->getSceneCoord();
        QPointF finalLoc = QPointF(itemLoc.x(), itemLoc.y());
        setCoordinate(tileToMoveTo->getCoordinate());
        graphicsItem_->setPos(finalLoc);
        cancelMovement();
        return true;
    }

    return false;
}

bool GraphicsUnitBase::canMoveToTile(GraphicsTileBase *tileToMoveTo)
{
    if (tileToMoveTo->getOwner() == nullptr || tileToMoveTo->getOwner() == getOwner()) {
        return tileToMoveTo->getMovementCost() <= movePoints_;
    } else {
        return false;
    }
}

void GraphicsUnitBase::switchTurn()
{
    movePoints_ = 2;
}

bool GraphicsUnitBase::isSelectable() const
{
        std::shared_ptr<GameEventHandler> eventHndlr =
                std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
        return !(eventHndlr->getCurrentPlayer() != getOwner() && getOwner() != nullptr);
}

void GraphicsUnitBase::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    graphicsItem_ = graphicsItem;
    scene_ = scene;

    graphicsItem_->setShapePref(DEFAULT);

    scene_->addItem(graphicsItem_);

    graphicsItem_->setPixmap(QPixmap(":/resources/units/worker.PNG"));
    graphicsItem_->setZValue(11);
    scene_->update();
}

void GraphicsUnitBase::cancelMovement()
{
    scene_->toggleTileHighlight(adjacentTilesTemp_);
    adjacentTilesTemp_.clear();
}

void GraphicsUnitBase::initMove()
{
    adjacentTilesTemp_.clear();
    scene_->enterMovementMode();
    std::shared_ptr<Course::TileBase> thisTile = lockObjectManager()->getTile(getCoordinate());
    scene_->getAdjacentTiles(adjacentTilesTemp_,
                             std::dynamic_pointer_cast<GraphicsTileBase>(thisTile), getMovePoints(), this);


    scene_->toggleTileHighlight(adjacentTilesTemp_, true);
}
