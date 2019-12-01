#include "worker.h"
#include "ui/customgraphicsscene.h"

Worker::Worker(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
               const std::shared_ptr<Course::iObjectManager> &objectmanager,
               const std::shared_ptr<Course::PlayerBase> &owner,
               CustomGraphicsScene *scene,
               const int &tilespaces,
               const Course::ResourceMap &cost,
               const Course::ResourceMapDouble &efficiency) :
    GraphicsUnitBase (eventhandler, objectmanager, owner, scene, tilespaces, cost, efficiency)
{
    movePoints_ = Units::LONGRANGE;
}

bool Worker::moveToTile(std::shared_ptr<GraphicsTileBase> tileToMoveTo, bool ignoreMovePoints)
{

}

bool Worker::canMoveToTile(GraphicsTileBase *tileToMoveTo)
{

}

void Worker::switchTurn()
{
    movePoints_ = Units::LONGRANGE;
}

void Worker::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    GraphicsUnitBase::setGraphicsItem(graphicsItem, scene);
    graphicsItem_->setPixmap(QPixmap(":/resources/units/scout.PNG"));
    scene_->update();
}

std::string Worker::getType() const
{
    return "Worker";
}

void Worker::getDescriptionBrief(std::string &desc)
{
    desc += "/n A hard-working fellow.";
}
