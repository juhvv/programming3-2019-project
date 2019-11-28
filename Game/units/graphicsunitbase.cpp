#include "graphicsunitbase.h"
#include "tiles/graphicstilebase.h"
#include "ui/customgraphicsscene.h"


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
    graphicsItem_->setZValue(5);

}

bool GraphicsUnitBase::isMovable() const
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
        setCoordinate(tileToMoveTo->getCoordinate());
        graphicsItem_->setPos(finalLoc);
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
    return true;
}

void GraphicsUnitBase::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    graphicsItem_ = graphicsItem;
    scene_ = scene;

    graphicsItem_->setShapePref(DEFAULT);

    graphicsItem_->setPixmap(QPixmap(":/resources/units/worker.PNG"));
    graphicsItem_->setZValue(11);
    scene_->update();
}
