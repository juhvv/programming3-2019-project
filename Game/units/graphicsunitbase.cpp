#include "graphicsunitbase.h"
#include "tiles/graphicstilebase.h"
#include "ui/customgraphicsscene.h"
#include "gameeventhandler.hh"
#include "exceptions/invalidpointer.h"


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
    QAction* titleDummyAction = menu.addAction(this->getType().c_str());
    titleDummyAction->setDisabled(true);
    menu.addSeparator();

    QAction* infoAction = menu.addAction("Info");

    if (std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler())->getCurrentPlayer() == getOwner()) {
        // add actions only available to unit's owner here
        std::string moveActionText = "Move - " + std::to_string(getMovePoints())
                + " move points left";
        QAction* moveAction = menu.addAction(moveActionText.c_str());

        if (movePoints_ == 0) {
            moveAction->setDisabled(true);
        }

        connect(moveAction, &QAction::triggered, this, &GraphicsUnitBase::initMove);
    }
    connect(infoAction, &QAction::triggered, this, &GraphicsUnitBase::sendInfo);
}

unsigned int GraphicsUnitBase::getMovePoints()
{
    return movePoints_;
}

bool GraphicsUnitBase::moveToTile(std::shared_ptr<GraphicsTileBase> tileToMoveTo, bool ignoreMovePoints)
{
    auto it = std::find(adjacentTilesTemp_.begin(), adjacentTilesTemp_.end(), tileToMoveTo->getGraphicsItem());
    if (it != adjacentTilesTemp_.end() || ignoreMovePoints) {
        if (!ignoreMovePoints) {
            movePoints_ -= tileToMoveTo->getMovementCost();
        }

        try {
            getCurrentTile()->removeUnit(this);

        } catch (Course::InvalidPointer) {
            qDebug() << "GraphicsUnitBase::moveToTile: no current tile";
        }

        tileToMoveTo->addUnit(this);

        setCoordinate(tileToMoveTo->getCoordinate());

        QPointF itemLoc = tileToMoveTo->getSceneCoord();
        QPointF finalLoc = QPointF(itemLoc.x(), itemLoc.y());
        setCoordinate(tileToMoveTo->getCoordinate());
        graphicsItem_->setPos(finalLoc);

        cancelMovement();

        std::dynamic_pointer_cast<GameEventHandler>
                (lockEventHandler())->updateVisibleResources();

        return true;
    } else {
        std::dynamic_pointer_cast<GameEventHandler>
                (lockEventHandler())->sendMsg("Cant go there.");
        return false;
    }
}

bool GraphicsUnitBase::canMoveToTile(GraphicsTileBase *tileToMoveTo)
{
    if (tileToMoveTo->getOwner() == getOwner()) {
        return tileToMoveTo->getMovementCost() <= movePoints_
                && tileToMoveTo->hasSpaceForWorkers(spacesInTileCapacity());
    }
    return false;
}

void GraphicsUnitBase::switchTurn()
{
    cancelMovement();
}

bool GraphicsUnitBase::isSelectable() const
{
    return true;
}

void GraphicsUnitBase::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    graphicsItem_ = graphicsItem;
    scene_ = scene;

    graphicsItem_->setShapePref(shapePrefs::DEFAULT);

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

void GraphicsUnitBase::getDescriptionBrief(std::string &desc)
{
    desc += "\n Oispa description";
}

std::shared_ptr<GraphicsTileBase> GraphicsUnitBase::getCurrentTile()
{
    return std::dynamic_pointer_cast<GraphicsTileBase>
                    (lockObjectManager()->getTile(getCoordinate()));
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

void GraphicsUnitBase::sendInfo()
{
    std::string infoMsg = getOwner()->getName() + "'s " + getType();
    getDescriptionBrief(infoMsg);

    std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler())->sendMsg(infoMsg);
}
