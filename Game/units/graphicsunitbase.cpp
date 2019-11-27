#include "graphicsunitbase.h"
#include "tiles/graphicstilebase.h"


GraphicsUnitBase::GraphicsUnitBase(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                                   const std::shared_ptr<Course::PlayerBase> &owner,
                                   CustomGraphicsScene* scene,
                                   const int &tilespaces,
                                   const Course::ResourceMap &cost,
                                   const Course::ResourceMapDouble &efficiency) :
    GameObjectBase (scene),
    Course::WorkerBase (eventhandler, objectmanager, owner)
{
    graphicsItem_->setZValue(5);

}

bool GraphicsUnitBase::isMovable()
{
    return true;
}

void GraphicsUnitBase::getMenuItems(QMenu &menu)
{
    QAction* infoAction = menu.addAction("Info");
}

void GraphicsUnitBase::doSpecialAction()
{

}

unsigned int GraphicsUnitBase::getMovePoints()
{
    return movePoints_;
}

bool GraphicsUnitBase::moveToTile(std::shared_ptr<GraphicsTileBase> tileToMoveTo)
{
    if (canMoveToTile(tileToMoveTo.get())) {
        --movePoints_;
        QPointF newLoc = tileToMoveTo->getSceneCoord();
        QPointF finalLoc = QPointF(newLoc.x() + 28, newLoc.y() + 28);
        graphicsItem_->setPos(finalLoc);
    }
}

bool GraphicsUnitBase::canMoveToTile(GraphicsTileBase *tileToMoveTo)
{
    if (tileToMoveTo->getOwner() == nullptr || tileToMoveTo->getOwner() == getOwner()) {
        return tileToMoveTo->getMovementCost() <= movePoints_;
    }
}

void GraphicsUnitBase::switchTurn()
{
    movePoints_ = 2;
}

bool GraphicsUnitBase::isSelectable()
{
    return true;
}
